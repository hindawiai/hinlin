<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <uapi/linux/idxd.h>
#समावेश "registers.h"
#समावेश "idxd.h"

अटल अक्षर *idxd_wq_type_names[] = अणु
	[IDXD_WQT_NONE]		= "none",
	[IDXD_WQT_KERNEL]	= "kernel",
	[IDXD_WQT_USER]		= "user",
पूर्ण;

अटल पूर्णांक idxd_config_bus_match(काष्ठा device *dev,
				 काष्ठा device_driver *drv)
अणु
	पूर्णांक matched = 0;

	अगर (is_idxd_dev(dev)) अणु
		काष्ठा idxd_device *idxd = confdev_to_idxd(dev);

		अगर (idxd->state != IDXD_DEV_CONF_READY)
			वापस 0;
		matched = 1;
	पूर्ण अन्यथा अगर (is_idxd_wq_dev(dev)) अणु
		काष्ठा idxd_wq *wq = confdev_to_wq(dev);
		काष्ठा idxd_device *idxd = wq->idxd;

		अगर (idxd->state < IDXD_DEV_CONF_READY)
			वापस 0;

		अगर (wq->state != IDXD_WQ_DISABLED) अणु
			dev_dbg(dev, "%s not disabled\n", dev_name(dev));
			वापस 0;
		पूर्ण
		matched = 1;
	पूर्ण

	अगर (matched)
		dev_dbg(dev, "%s matched\n", dev_name(dev));

	वापस matched;
पूर्ण

अटल पूर्णांक enable_wq(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	mutex_lock(&wq->wq_lock);

	अगर (idxd->state != IDXD_DEV_ENABLED) अणु
		mutex_unlock(&wq->wq_lock);
		dev_warn(dev, "Enabling while device not enabled.\n");
		वापस -EPERM;
	पूर्ण

	अगर (wq->state != IDXD_WQ_DISABLED) अणु
		mutex_unlock(&wq->wq_lock);
		dev_warn(dev, "WQ %d already enabled.\n", wq->id);
		वापस -EBUSY;
	पूर्ण

	अगर (!wq->group) अणु
		mutex_unlock(&wq->wq_lock);
		dev_warn(dev, "WQ not attached to group.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (म_माप(wq->name) == 0) अणु
		mutex_unlock(&wq->wq_lock);
		dev_warn(dev, "WQ name not set.\n");
		वापस -EINVAL;
	पूर्ण

	/* Shared WQ checks */
	अगर (wq_shared(wq)) अणु
		अगर (!device_swq_supported(idxd)) अणु
			dev_warn(dev, "PASID not enabled and shared WQ.\n");
			mutex_unlock(&wq->wq_lock);
			वापस -ENXIO;
		पूर्ण
		/*
		 * Shared wq with the threshold set to 0 means the user
		 * did not set the threshold or transitioned from a
		 * dedicated wq but did not set threshold. A value
		 * of 0 would effectively disable the shared wq. The
		 * driver करोes not allow a value of 0 to be set क्रम
		 * threshold via sysfs.
		 */
		अगर (wq->threshold == 0) अणु
			dev_warn(dev, "Shared WQ and threshold 0.\n");
			mutex_unlock(&wq->wq_lock);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	rc = idxd_wq_alloc_resources(wq);
	अगर (rc < 0) अणु
		mutex_unlock(&wq->wq_lock);
		dev_warn(dev, "WQ resource alloc failed\n");
		वापस rc;
	पूर्ण

	spin_lock_irqsave(&idxd->dev_lock, flags);
	अगर (test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		rc = idxd_device_config(idxd);
	spin_unlock_irqrestore(&idxd->dev_lock, flags);
	अगर (rc < 0) अणु
		mutex_unlock(&wq->wq_lock);
		dev_warn(dev, "Writing WQ %d config failed: %d\n", wq->id, rc);
		वापस rc;
	पूर्ण

	rc = idxd_wq_enable(wq);
	अगर (rc < 0) अणु
		mutex_unlock(&wq->wq_lock);
		dev_warn(dev, "WQ %d enabling failed: %d\n", wq->id, rc);
		वापस rc;
	पूर्ण

	rc = idxd_wq_map_portal(wq);
	अगर (rc < 0) अणु
		dev_warn(dev, "wq portal mapping failed: %d\n", rc);
		rc = idxd_wq_disable(wq);
		अगर (rc < 0)
			dev_warn(dev, "IDXD wq disable failed\n");
		mutex_unlock(&wq->wq_lock);
		वापस rc;
	पूर्ण

	wq->client_count = 0;

	अगर (wq->type == IDXD_WQT_KERNEL) अणु
		rc = idxd_wq_init_percpu_ref(wq);
		अगर (rc < 0) अणु
			dev_dbg(dev, "percpu_ref setup failed\n");
			mutex_unlock(&wq->wq_lock);
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (is_idxd_wq_dmaengine(wq)) अणु
		rc = idxd_रेजिस्टर_dma_channel(wq);
		अगर (rc < 0) अणु
			dev_dbg(dev, "DMA channel register failed\n");
			mutex_unlock(&wq->wq_lock);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अगर (is_idxd_wq_cdev(wq)) अणु
		rc = idxd_wq_add_cdev(wq);
		अगर (rc < 0) अणु
			dev_dbg(dev, "Cdev creation failed\n");
			mutex_unlock(&wq->wq_lock);
			वापस rc;
		पूर्ण
	पूर्ण

	mutex_unlock(&wq->wq_lock);
	dev_info(dev, "wq %s enabled\n", dev_name(&wq->conf_dev));

	वापस 0;
पूर्ण

अटल पूर्णांक idxd_config_bus_probe(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;

	dev_dbg(dev, "%s called\n", __func__);

	अगर (is_idxd_dev(dev)) अणु
		काष्ठा idxd_device *idxd = confdev_to_idxd(dev);

		अगर (idxd->state != IDXD_DEV_CONF_READY) अणु
			dev_warn(dev, "Device not ready for config\n");
			वापस -EBUSY;
		पूर्ण

		अगर (!try_module_get(THIS_MODULE))
			वापस -ENXIO;

		/* Perक्रमm IDXD configuration and enabling */
		spin_lock_irqsave(&idxd->dev_lock, flags);
		अगर (test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
			rc = idxd_device_config(idxd);
		spin_unlock_irqrestore(&idxd->dev_lock, flags);
		अगर (rc < 0) अणु
			module_put(THIS_MODULE);
			dev_warn(dev, "Device config failed: %d\n", rc);
			वापस rc;
		पूर्ण

		/* start device */
		rc = idxd_device_enable(idxd);
		अगर (rc < 0) अणु
			module_put(THIS_MODULE);
			dev_warn(dev, "Device enable failed: %d\n", rc);
			वापस rc;
		पूर्ण

		dev_info(dev, "Device %s enabled\n", dev_name(dev));

		rc = idxd_रेजिस्टर_dma_device(idxd);
		अगर (rc < 0) अणु
			module_put(THIS_MODULE);
			dev_dbg(dev, "Failed to register dmaengine device\n");
			वापस rc;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (is_idxd_wq_dev(dev)) अणु
		काष्ठा idxd_wq *wq = confdev_to_wq(dev);

		वापस enable_wq(wq);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम disable_wq(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;

	mutex_lock(&wq->wq_lock);
	dev_dbg(dev, "%s removing WQ %s\n", __func__, dev_name(&wq->conf_dev));
	अगर (wq->state == IDXD_WQ_DISABLED) अणु
		mutex_unlock(&wq->wq_lock);
		वापस;
	पूर्ण

	अगर (wq->type == IDXD_WQT_KERNEL)
		idxd_wq_quiesce(wq);

	अगर (is_idxd_wq_dmaengine(wq))
		idxd_unरेजिस्टर_dma_channel(wq);
	अन्यथा अगर (is_idxd_wq_cdev(wq))
		idxd_wq_del_cdev(wq);

	अगर (idxd_wq_refcount(wq))
		dev_warn(dev, "Clients has claim on wq %d: %d\n",
			 wq->id, idxd_wq_refcount(wq));

	idxd_wq_unmap_portal(wq);

	idxd_wq_drain(wq);
	idxd_wq_reset(wq);

	idxd_wq_मुक्त_resources(wq);
	wq->client_count = 0;
	mutex_unlock(&wq->wq_lock);

	dev_info(dev, "wq %s disabled\n", dev_name(&wq->conf_dev));
पूर्ण

अटल पूर्णांक idxd_config_bus_हटाओ(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	dev_dbg(dev, "%s called for %s\n", __func__, dev_name(dev));

	/* disable workqueue here */
	अगर (is_idxd_wq_dev(dev)) अणु
		काष्ठा idxd_wq *wq = confdev_to_wq(dev);

		disable_wq(wq);
	पूर्ण अन्यथा अगर (is_idxd_dev(dev)) अणु
		काष्ठा idxd_device *idxd = confdev_to_idxd(dev);
		पूर्णांक i;

		dev_dbg(dev, "%s removing dev %s\n", __func__,
			dev_name(&idxd->conf_dev));
		क्रम (i = 0; i < idxd->max_wqs; i++) अणु
			काष्ठा idxd_wq *wq = idxd->wqs[i];

			अगर (wq->state == IDXD_WQ_DISABLED)
				जारी;
			dev_warn(dev, "Active wq %d on disable %s.\n", i,
				 dev_name(&idxd->conf_dev));
			device_release_driver(&wq->conf_dev);
		पूर्ण

		idxd_unरेजिस्टर_dma_device(idxd);
		rc = idxd_device_disable(idxd);
		अगर (test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags)) अणु
			क्रम (i = 0; i < idxd->max_wqs; i++) अणु
				काष्ठा idxd_wq *wq = idxd->wqs[i];

				mutex_lock(&wq->wq_lock);
				idxd_wq_disable_cleanup(wq);
				mutex_unlock(&wq->wq_lock);
			पूर्ण
		पूर्ण
		module_put(THIS_MODULE);
		अगर (rc < 0)
			dev_warn(dev, "Device disable failed\n");
		अन्यथा
			dev_info(dev, "Device %s disabled\n", dev_name(dev));

	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम idxd_config_bus_shutकरोwn(काष्ठा device *dev)
अणु
	dev_dbg(dev, "%s called\n", __func__);
पूर्ण

काष्ठा bus_type dsa_bus_type = अणु
	.name = "dsa",
	.match = idxd_config_bus_match,
	.probe = idxd_config_bus_probe,
	.हटाओ = idxd_config_bus_हटाओ,
	.shutकरोwn = idxd_config_bus_shutकरोwn,
पूर्ण;

अटल काष्ठा idxd_device_driver dsa_drv = अणु
	.drv = अणु
		.name = "dsa",
		.bus = &dsa_bus_type,
		.owner = THIS_MODULE,
		.mod_name = KBUILD_MODNAME,
	पूर्ण,
पूर्ण;

/* IDXD generic driver setup */
पूर्णांक idxd_रेजिस्टर_driver(व्योम)
अणु
	वापस driver_रेजिस्टर(&dsa_drv.drv);
पूर्ण

व्योम idxd_unरेजिस्टर_driver(व्योम)
अणु
	driver_unरेजिस्टर(&dsa_drv.drv);
पूर्ण

/* IDXD engine attributes */
अटल sमाप_प्रकार engine_group_id_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_engine *engine =
		container_of(dev, काष्ठा idxd_engine, conf_dev);

	अगर (engine->group)
		वापस sysfs_emit(buf, "%d\n", engine->group->id);
	अन्यथा
		वापस sysfs_emit(buf, "%d\n", -1);
पूर्ण

अटल sमाप_प्रकार engine_group_id_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_engine *engine =
		container_of(dev, काष्ठा idxd_engine, conf_dev);
	काष्ठा idxd_device *idxd = engine->idxd;
	दीर्घ id;
	पूर्णांक rc;
	काष्ठा idxd_group *prevg;

	rc = kम_से_दीर्घ(buf, 10, &id);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (id > idxd->max_groups - 1 || id < -1)
		वापस -EINVAL;

	अगर (id == -1) अणु
		अगर (engine->group) अणु
			engine->group->num_engines--;
			engine->group = शून्य;
		पूर्ण
		वापस count;
	पूर्ण

	prevg = engine->group;

	अगर (prevg)
		prevg->num_engines--;
	engine->group = idxd->groups[id];
	engine->group->num_engines++;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_engine_group =
		__ATTR(group_id, 0644, engine_group_id_show,
		       engine_group_id_store);

अटल काष्ठा attribute *idxd_engine_attributes[] = अणु
	&dev_attr_engine_group.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group idxd_engine_attribute_group = अणु
	.attrs = idxd_engine_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *idxd_engine_attribute_groups[] = अणु
	&idxd_engine_attribute_group,
	शून्य,
पूर्ण;

अटल व्योम idxd_conf_engine_release(काष्ठा device *dev)
अणु
	काष्ठा idxd_engine *engine = container_of(dev, काष्ठा idxd_engine, conf_dev);

	kमुक्त(engine);
पूर्ण

काष्ठा device_type idxd_engine_device_type = अणु
	.name = "engine",
	.release = idxd_conf_engine_release,
	.groups = idxd_engine_attribute_groups,
पूर्ण;

/* Group attributes */

अटल व्योम idxd_set_मुक्त_tokens(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i, tokens;

	क्रम (i = 0, tokens = 0; i < idxd->max_groups; i++) अणु
		काष्ठा idxd_group *g = idxd->groups[i];

		tokens += g->tokens_reserved;
	पूर्ण

	idxd->nr_tokens = idxd->max_tokens - tokens;
पूर्ण

अटल sमाप_प्रकार group_tokens_reserved_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);

	वापस sysfs_emit(buf, "%u\n", group->tokens_reserved);
पूर्ण

अटल sमाप_प्रकार group_tokens_reserved_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);
	काष्ठा idxd_device *idxd = group->idxd;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 10, &val);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (idxd->data->type == IDXD_TYPE_IAX)
		वापस -EOPNOTSUPP;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (idxd->state == IDXD_DEV_ENABLED)
		वापस -EPERM;

	अगर (val > idxd->max_tokens)
		वापस -EINVAL;

	अगर (val > idxd->nr_tokens + group->tokens_reserved)
		वापस -EINVAL;

	group->tokens_reserved = val;
	idxd_set_मुक्त_tokens(idxd);
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_group_tokens_reserved =
		__ATTR(tokens_reserved, 0644, group_tokens_reserved_show,
		       group_tokens_reserved_store);

अटल sमाप_प्रकार group_tokens_allowed_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);

	वापस sysfs_emit(buf, "%u\n", group->tokens_allowed);
पूर्ण

अटल sमाप_प्रकार group_tokens_allowed_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);
	काष्ठा idxd_device *idxd = group->idxd;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 10, &val);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (idxd->data->type == IDXD_TYPE_IAX)
		वापस -EOPNOTSUPP;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (idxd->state == IDXD_DEV_ENABLED)
		वापस -EPERM;

	अगर (val < 4 * group->num_engines ||
	    val > group->tokens_reserved + idxd->nr_tokens)
		वापस -EINVAL;

	group->tokens_allowed = val;
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_group_tokens_allowed =
		__ATTR(tokens_allowed, 0644, group_tokens_allowed_show,
		       group_tokens_allowed_store);

अटल sमाप_प्रकार group_use_token_limit_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);

	वापस sysfs_emit(buf, "%u\n", group->use_token_limit);
पूर्ण

अटल sमाप_प्रकार group_use_token_limit_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);
	काष्ठा idxd_device *idxd = group->idxd;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 10, &val);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (idxd->data->type == IDXD_TYPE_IAX)
		वापस -EOPNOTSUPP;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (idxd->state == IDXD_DEV_ENABLED)
		वापस -EPERM;

	अगर (idxd->token_limit == 0)
		वापस -EPERM;

	group->use_token_limit = !!val;
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_group_use_token_limit =
		__ATTR(use_token_limit, 0644, group_use_token_limit_show,
		       group_use_token_limit_store);

अटल sमाप_प्रकार group_engines_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);
	पूर्णांक i, rc = 0;
	काष्ठा idxd_device *idxd = group->idxd;

	क्रम (i = 0; i < idxd->max_engines; i++) अणु
		काष्ठा idxd_engine *engine = idxd->engines[i];

		अगर (!engine->group)
			जारी;

		अगर (engine->group->id == group->id)
			rc += sysfs_emit_at(buf, rc, "engine%d.%d ", idxd->id, engine->id);
	पूर्ण

	अगर (!rc)
		वापस 0;
	rc--;
	rc += sysfs_emit_at(buf, rc, "\n");

	वापस rc;
पूर्ण

अटल काष्ठा device_attribute dev_attr_group_engines =
		__ATTR(engines, 0444, group_engines_show, शून्य);

अटल sमाप_प्रकार group_work_queues_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);
	पूर्णांक i, rc = 0;
	काष्ठा idxd_device *idxd = group->idxd;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		अगर (!wq->group)
			जारी;

		अगर (wq->group->id == group->id)
			rc += sysfs_emit_at(buf, rc, "wq%d.%d ", idxd->id, wq->id);
	पूर्ण

	अगर (!rc)
		वापस 0;
	rc--;
	rc += sysfs_emit_at(buf, rc, "\n");

	वापस rc;
पूर्ण

अटल काष्ठा device_attribute dev_attr_group_work_queues =
		__ATTR(work_queues, 0444, group_work_queues_show, शून्य);

अटल sमाप_प्रकार group_traffic_class_a_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);

	वापस sysfs_emit(buf, "%d\n", group->tc_a);
पूर्ण

अटल sमाप_प्रकार group_traffic_class_a_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);
	काष्ठा idxd_device *idxd = group->idxd;
	दीर्घ val;
	पूर्णांक rc;

	rc = kम_से_दीर्घ(buf, 10, &val);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (idxd->state == IDXD_DEV_ENABLED)
		वापस -EPERM;

	अगर (val < 0 || val > 7)
		वापस -EINVAL;

	group->tc_a = val;
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_group_traffic_class_a =
		__ATTR(traffic_class_a, 0644, group_traffic_class_a_show,
		       group_traffic_class_a_store);

अटल sमाप_प्रकार group_traffic_class_b_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);

	वापस sysfs_emit(buf, "%d\n", group->tc_b);
पूर्ण

अटल sमाप_प्रकार group_traffic_class_b_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_group *group =
		container_of(dev, काष्ठा idxd_group, conf_dev);
	काष्ठा idxd_device *idxd = group->idxd;
	दीर्घ val;
	पूर्णांक rc;

	rc = kम_से_दीर्घ(buf, 10, &val);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (idxd->state == IDXD_DEV_ENABLED)
		वापस -EPERM;

	अगर (val < 0 || val > 7)
		वापस -EINVAL;

	group->tc_b = val;
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_group_traffic_class_b =
		__ATTR(traffic_class_b, 0644, group_traffic_class_b_show,
		       group_traffic_class_b_store);

अटल काष्ठा attribute *idxd_group_attributes[] = अणु
	&dev_attr_group_work_queues.attr,
	&dev_attr_group_engines.attr,
	&dev_attr_group_use_token_limit.attr,
	&dev_attr_group_tokens_allowed.attr,
	&dev_attr_group_tokens_reserved.attr,
	&dev_attr_group_traffic_class_a.attr,
	&dev_attr_group_traffic_class_b.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group idxd_group_attribute_group = अणु
	.attrs = idxd_group_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *idxd_group_attribute_groups[] = अणु
	&idxd_group_attribute_group,
	शून्य,
पूर्ण;

अटल व्योम idxd_conf_group_release(काष्ठा device *dev)
अणु
	काष्ठा idxd_group *group = container_of(dev, काष्ठा idxd_group, conf_dev);

	kमुक्त(group);
पूर्ण

काष्ठा device_type idxd_group_device_type = अणु
	.name = "group",
	.release = idxd_conf_group_release,
	.groups = idxd_group_attribute_groups,
पूर्ण;

/* IDXD work queue attribs */
अटल sमाप_प्रकार wq_clients_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%d\n", wq->client_count);
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_clients =
		__ATTR(clients, 0444, wq_clients_show, शून्य);

अटल sमाप_प्रकार wq_state_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	चयन (wq->state) अणु
	हाल IDXD_WQ_DISABLED:
		वापस sysfs_emit(buf, "disabled\n");
	हाल IDXD_WQ_ENABLED:
		वापस sysfs_emit(buf, "enabled\n");
	पूर्ण

	वापस sysfs_emit(buf, "unknown\n");
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_state =
		__ATTR(state, 0444, wq_state_show, शून्य);

अटल sमाप_प्रकार wq_group_id_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	अगर (wq->group)
		वापस sysfs_emit(buf, "%u\n", wq->group->id);
	अन्यथा
		वापस sysfs_emit(buf, "-1\n");
पूर्ण

अटल sमाप_प्रकार wq_group_id_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	काष्ठा idxd_device *idxd = wq->idxd;
	दीर्घ id;
	पूर्णांक rc;
	काष्ठा idxd_group *prevg, *group;

	rc = kम_से_दीर्घ(buf, 10, &id);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -EPERM;

	अगर (id > idxd->max_groups - 1 || id < -1)
		वापस -EINVAL;

	अगर (id == -1) अणु
		अगर (wq->group) अणु
			wq->group->num_wqs--;
			wq->group = शून्य;
		पूर्ण
		वापस count;
	पूर्ण

	group = idxd->groups[id];
	prevg = wq->group;

	अगर (prevg)
		prevg->num_wqs--;
	wq->group = group;
	group->num_wqs++;
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_group_id =
		__ATTR(group_id, 0644, wq_group_id_show, wq_group_id_store);

अटल sमाप_प्रकार wq_mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%s\n", wq_dedicated(wq) ? "dedicated" : "shared");
पूर्ण

अटल sमाप_प्रकार wq_mode_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	काष्ठा idxd_device *idxd = wq->idxd;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -EPERM;

	अगर (sysfs_streq(buf, "dedicated")) अणु
		set_bit(WQ_FLAG_DEDICATED, &wq->flags);
		wq->threshold = 0;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "shared") && device_swq_supported(idxd)) अणु
		clear_bit(WQ_FLAG_DEDICATED, &wq->flags);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_mode =
		__ATTR(mode, 0644, wq_mode_show, wq_mode_store);

अटल sमाप_प्रकार wq_size_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%u\n", wq->size);
पूर्ण

अटल पूर्णांक total_claimed_wq_size(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i;
	पूर्णांक wq_size = 0;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		wq_size += wq->size;
	पूर्ण

	वापस wq_size;
पूर्ण

अटल sमाप_प्रकार wq_size_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	अचिन्हित दीर्घ size;
	काष्ठा idxd_device *idxd = wq->idxd;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 10, &size);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (idxd->state == IDXD_DEV_ENABLED)
		वापस -EPERM;

	अगर (size + total_claimed_wq_size(idxd) - wq->size > idxd->max_wq_size)
		वापस -EINVAL;

	wq->size = size;
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_size =
		__ATTR(size, 0644, wq_size_show, wq_size_store);

अटल sमाप_प्रकार wq_priority_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%u\n", wq->priority);
पूर्ण

अटल sमाप_प्रकार wq_priority_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	अचिन्हित दीर्घ prio;
	काष्ठा idxd_device *idxd = wq->idxd;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 10, &prio);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -EPERM;

	अगर (prio > IDXD_MAX_PRIORITY)
		वापस -EINVAL;

	wq->priority = prio;
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_priority =
		__ATTR(priority, 0644, wq_priority_show, wq_priority_store);

अटल sमाप_प्रकार wq_block_on_fault_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%u\n", test_bit(WQ_FLAG_BLOCK_ON_FAULT, &wq->flags));
पूर्ण

अटल sमाप_प्रकार wq_block_on_fault_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	काष्ठा idxd_device *idxd = wq->idxd;
	bool bof;
	पूर्णांक rc;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -ENXIO;

	rc = kstrtobool(buf, &bof);
	अगर (rc < 0)
		वापस rc;

	अगर (bof)
		set_bit(WQ_FLAG_BLOCK_ON_FAULT, &wq->flags);
	अन्यथा
		clear_bit(WQ_FLAG_BLOCK_ON_FAULT, &wq->flags);

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_block_on_fault =
		__ATTR(block_on_fault, 0644, wq_block_on_fault_show,
		       wq_block_on_fault_store);

अटल sमाप_प्रकार wq_threshold_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%u\n", wq->threshold);
पूर्ण

अटल sमाप_प्रकार wq_threshold_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	काष्ठा idxd_device *idxd = wq->idxd;
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	rc = kstrtouपूर्णांक(buf, 0, &val);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (val > wq->size || val <= 0)
		वापस -EINVAL;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -ENXIO;

	अगर (test_bit(WQ_FLAG_DEDICATED, &wq->flags))
		वापस -EINVAL;

	wq->threshold = val;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_threshold =
		__ATTR(threshold, 0644, wq_threshold_show, wq_threshold_store);

अटल sमाप_प्रकार wq_type_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	चयन (wq->type) अणु
	हाल IDXD_WQT_KERNEL:
		वापस sysfs_emit(buf, "%s\n", idxd_wq_type_names[IDXD_WQT_KERNEL]);
	हाल IDXD_WQT_USER:
		वापस sysfs_emit(buf, "%s\n", idxd_wq_type_names[IDXD_WQT_USER]);
	हाल IDXD_WQT_NONE:
	शेष:
		वापस sysfs_emit(buf, "%s\n", idxd_wq_type_names[IDXD_WQT_NONE]);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार wq_type_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	क्रमागत idxd_wq_type old_type;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -EPERM;

	old_type = wq->type;
	अगर (sysfs_streq(buf, idxd_wq_type_names[IDXD_WQT_NONE]))
		wq->type = IDXD_WQT_NONE;
	अन्यथा अगर (sysfs_streq(buf, idxd_wq_type_names[IDXD_WQT_KERNEL]))
		wq->type = IDXD_WQT_KERNEL;
	अन्यथा अगर (sysfs_streq(buf, idxd_wq_type_names[IDXD_WQT_USER]))
		wq->type = IDXD_WQT_USER;
	अन्यथा
		वापस -EINVAL;

	/* If we are changing queue type, clear the name */
	अगर (wq->type != old_type)
		स_रखो(wq->name, 0, WQ_NAME_SIZE + 1);

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_type =
		__ATTR(type, 0644, wq_type_show, wq_type_store);

अटल sमाप_प्रकार wq_name_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%s\n", wq->name);
पूर्ण

अटल sमाप_प्रकार wq_name_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -EPERM;

	अगर (म_माप(buf) > WQ_NAME_SIZE || म_माप(buf) == 0)
		वापस -EINVAL;

	/*
	 * This is temporarily placed here until we have SVM support क्रम
	 * dmaengine.
	 */
	अगर (wq->type == IDXD_WQT_KERNEL && device_pasid_enabled(wq->idxd))
		वापस -EOPNOTSUPP;

	स_रखो(wq->name, 0, WQ_NAME_SIZE + 1);
	म_नकलन(wq->name, buf, WQ_NAME_SIZE);
	strreplace(wq->name, '\n', '\0');
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_name =
		__ATTR(name, 0644, wq_name_show, wq_name_store);

अटल sमाप_प्रकार wq_cdev_minor_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	पूर्णांक minor = -1;

	mutex_lock(&wq->wq_lock);
	अगर (wq->idxd_cdev)
		minor = wq->idxd_cdev->minor;
	mutex_unlock(&wq->wq_lock);

	अगर (minor == -1)
		वापस -ENXIO;
	वापस sysfs_emit(buf, "%d\n", minor);
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_cdev_minor =
		__ATTR(cdev_minor, 0444, wq_cdev_minor_show, शून्य);

अटल पूर्णांक __get_sysfs_u64(स्थिर अक्षर *buf, u64 *val)
अणु
	पूर्णांक rc;

	rc = kstrtou64(buf, 0, val);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (*val == 0)
		वापस -EINVAL;

	*val = roundup_घात_of_two(*val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार wq_max_transfer_size_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%llu\n", wq->max_xfer_bytes);
पूर्ण

अटल sमाप_प्रकार wq_max_transfer_size_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	काष्ठा idxd_device *idxd = wq->idxd;
	u64 xfer_size;
	पूर्णांक rc;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -EPERM;

	rc = __get_sysfs_u64(buf, &xfer_size);
	अगर (rc < 0)
		वापस rc;

	अगर (xfer_size > idxd->max_xfer_bytes)
		वापस -EINVAL;

	wq->max_xfer_bytes = xfer_size;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_max_transfer_size =
		__ATTR(max_transfer_size, 0644,
		       wq_max_transfer_size_show, wq_max_transfer_size_store);

अटल sमाप_प्रकार wq_max_batch_size_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%u\n", wq->max_batch_size);
पूर्ण

अटल sमाप_प्रकार wq_max_batch_size_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	काष्ठा idxd_device *idxd = wq->idxd;
	u64 batch_size;
	पूर्णांक rc;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -EPERM;

	rc = __get_sysfs_u64(buf, &batch_size);
	अगर (rc < 0)
		वापस rc;

	अगर (batch_size > idxd->max_batch_size)
		वापस -EINVAL;

	wq->max_batch_size = (u32)batch_size;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_max_batch_size =
		__ATTR(max_batch_size, 0644, wq_max_batch_size_show, wq_max_batch_size_store);

अटल sमाप_प्रकार wq_ats_disable_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	वापस sysfs_emit(buf, "%u\n", wq->ats_dis);
पूर्ण

अटल sमाप_प्रकार wq_ats_disable_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);
	काष्ठा idxd_device *idxd = wq->idxd;
	bool ats_dis;
	पूर्णांक rc;

	अगर (wq->state != IDXD_WQ_DISABLED)
		वापस -EPERM;

	अगर (!idxd->hw.wq_cap.wq_ats_support)
		वापस -EOPNOTSUPP;

	rc = kstrtobool(buf, &ats_dis);
	अगर (rc < 0)
		वापस rc;

	wq->ats_dis = ats_dis;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_wq_ats_disable =
		__ATTR(ats_disable, 0644, wq_ats_disable_show, wq_ats_disable_store);

अटल काष्ठा attribute *idxd_wq_attributes[] = अणु
	&dev_attr_wq_clients.attr,
	&dev_attr_wq_state.attr,
	&dev_attr_wq_group_id.attr,
	&dev_attr_wq_mode.attr,
	&dev_attr_wq_size.attr,
	&dev_attr_wq_priority.attr,
	&dev_attr_wq_block_on_fault.attr,
	&dev_attr_wq_threshold.attr,
	&dev_attr_wq_type.attr,
	&dev_attr_wq_name.attr,
	&dev_attr_wq_cdev_minor.attr,
	&dev_attr_wq_max_transfer_size.attr,
	&dev_attr_wq_max_batch_size.attr,
	&dev_attr_wq_ats_disable.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group idxd_wq_attribute_group = अणु
	.attrs = idxd_wq_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *idxd_wq_attribute_groups[] = अणु
	&idxd_wq_attribute_group,
	शून्य,
पूर्ण;

अटल व्योम idxd_conf_wq_release(काष्ठा device *dev)
अणु
	काष्ठा idxd_wq *wq = container_of(dev, काष्ठा idxd_wq, conf_dev);

	kमुक्त(wq->wqcfg);
	kमुक्त(wq);
पूर्ण

काष्ठा device_type idxd_wq_device_type = अणु
	.name = "wq",
	.release = idxd_conf_wq_release,
	.groups = idxd_wq_attribute_groups,
पूर्ण;

/* IDXD device attribs */
अटल sमाप_प्रकार version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%#x\n", idxd->hw.version);
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार max_work_queues_size_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", idxd->max_wq_size);
पूर्ण
अटल DEVICE_ATTR_RO(max_work_queues_size);

अटल sमाप_प्रकार max_groups_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", idxd->max_groups);
पूर्ण
अटल DEVICE_ATTR_RO(max_groups);

अटल sमाप_प्रकार max_work_queues_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", idxd->max_wqs);
पूर्ण
अटल DEVICE_ATTR_RO(max_work_queues);

अटल sमाप_प्रकार max_engines_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", idxd->max_engines);
पूर्ण
अटल DEVICE_ATTR_RO(max_engines);

अटल sमाप_प्रकार numa_node_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%d\n", dev_to_node(&idxd->pdev->dev));
पूर्ण
अटल DEVICE_ATTR_RO(numa_node);

अटल sमाप_प्रकार max_batch_size_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", idxd->max_batch_size);
पूर्ण
अटल DEVICE_ATTR_RO(max_batch_size);

अटल sमाप_प्रकार max_transfer_size_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%llu\n", idxd->max_xfer_bytes);
पूर्ण
अटल DEVICE_ATTR_RO(max_transfer_size);

अटल sमाप_प्रकार op_cap_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < 4; i++)
		rc += sysfs_emit_at(buf, rc, "%#llx ", idxd->hw.opcap.bits[i]);

	rc--;
	rc += sysfs_emit_at(buf, rc, "\n");
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(op_cap);

अटल sमाप_प्रकार gen_cap_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%#llx\n", idxd->hw.gen_cap.bits);
पूर्ण
अटल DEVICE_ATTR_RO(gen_cap);

अटल sमाप_प्रकार configurable_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags));
पूर्ण
अटल DEVICE_ATTR_RO(configurable);

अटल sमाप_प्रकार clients_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक count = 0, i;

	spin_lock_irqsave(&idxd->dev_lock, flags);
	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		count += wq->client_count;
	पूर्ण
	spin_unlock_irqrestore(&idxd->dev_lock, flags);

	वापस sysfs_emit(buf, "%d\n", count);
पूर्ण
अटल DEVICE_ATTR_RO(clients);

अटल sमाप_प्रकार pasid_enabled_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", device_pasid_enabled(idxd));
पूर्ण
अटल DEVICE_ATTR_RO(pasid_enabled);

अटल sमाप_प्रकार state_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	चयन (idxd->state) अणु
	हाल IDXD_DEV_DISABLED:
	हाल IDXD_DEV_CONF_READY:
		वापस sysfs_emit(buf, "disabled\n");
	हाल IDXD_DEV_ENABLED:
		वापस sysfs_emit(buf, "enabled\n");
	हाल IDXD_DEV_HALTED:
		वापस sysfs_emit(buf, "halted\n");
	पूर्ण

	वापस sysfs_emit(buf, "unknown\n");
पूर्ण
अटल DEVICE_ATTR_RO(state);

अटल sमाप_प्रकार errors_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);
	पूर्णांक i, out = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&idxd->dev_lock, flags);
	क्रम (i = 0; i < 4; i++)
		out += sysfs_emit_at(buf, out, "%#018llx ", idxd->sw_err.bits[i]);
	spin_unlock_irqrestore(&idxd->dev_lock, flags);
	out--;
	out += sysfs_emit_at(buf, out, "\n");
	वापस out;
पूर्ण
अटल DEVICE_ATTR_RO(errors);

अटल sमाप_प्रकार max_tokens_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", idxd->max_tokens);
पूर्ण
अटल DEVICE_ATTR_RO(max_tokens);

अटल sमाप_प्रकार token_limit_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", idxd->token_limit);
पूर्ण

अटल sमाप_प्रकार token_limit_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 10, &val);
	अगर (rc < 0)
		वापस -EINVAL;

	अगर (idxd->state == IDXD_DEV_ENABLED)
		वापस -EPERM;

	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags))
		वापस -EPERM;

	अगर (!idxd->hw.group_cap.token_limit)
		वापस -EPERM;

	अगर (val > idxd->hw.group_cap.total_tokens)
		वापस -EINVAL;

	idxd->token_limit = val;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(token_limit);

अटल sमाप_प्रकार cdev_major_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd =
		container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%u\n", idxd->major);
पूर्ण
अटल DEVICE_ATTR_RO(cdev_major);

अटल sमाप_प्रकार cmd_status_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idxd_device *idxd = container_of(dev, काष्ठा idxd_device, conf_dev);

	वापस sysfs_emit(buf, "%#x\n", idxd->cmd_status);
पूर्ण
अटल DEVICE_ATTR_RO(cmd_status);

अटल काष्ठा attribute *idxd_device_attributes[] = अणु
	&dev_attr_version.attr,
	&dev_attr_max_groups.attr,
	&dev_attr_max_work_queues.attr,
	&dev_attr_max_work_queues_size.attr,
	&dev_attr_max_engines.attr,
	&dev_attr_numa_node.attr,
	&dev_attr_max_batch_size.attr,
	&dev_attr_max_transfer_size.attr,
	&dev_attr_op_cap.attr,
	&dev_attr_gen_cap.attr,
	&dev_attr_configurable.attr,
	&dev_attr_clients.attr,
	&dev_attr_pasid_enabled.attr,
	&dev_attr_state.attr,
	&dev_attr_errors.attr,
	&dev_attr_max_tokens.attr,
	&dev_attr_token_limit.attr,
	&dev_attr_cdev_major.attr,
	&dev_attr_cmd_status.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group idxd_device_attribute_group = अणु
	.attrs = idxd_device_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *idxd_attribute_groups[] = अणु
	&idxd_device_attribute_group,
	शून्य,
पूर्ण;

अटल व्योम idxd_conf_device_release(काष्ठा device *dev)
अणु
	काष्ठा idxd_device *idxd = container_of(dev, काष्ठा idxd_device, conf_dev);

	kमुक्त(idxd->groups);
	kमुक्त(idxd->wqs);
	kमुक्त(idxd->engines);
	kमुक्त(idxd->irq_entries);
	kमुक्त(idxd->पूर्णांक_handles);
	ida_मुक्त(&idxd_ida, idxd->id);
	kमुक्त(idxd);
पूर्ण

काष्ठा device_type dsa_device_type = अणु
	.name = "dsa",
	.release = idxd_conf_device_release,
	.groups = idxd_attribute_groups,
पूर्ण;

काष्ठा device_type iax_device_type = अणु
	.name = "iax",
	.release = idxd_conf_device_release,
	.groups = idxd_attribute_groups,
पूर्ण;

अटल पूर्णांक idxd_रेजिस्टर_engine_devices(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i, j, rc;

	क्रम (i = 0; i < idxd->max_engines; i++) अणु
		काष्ठा idxd_engine *engine = idxd->engines[i];

		rc = device_add(&engine->conf_dev);
		अगर (rc < 0)
			जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	j = i - 1;
	क्रम (; i < idxd->max_engines; i++)
		put_device(&idxd->engines[i]->conf_dev);

	जबतक (j--)
		device_unरेजिस्टर(&idxd->engines[j]->conf_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक idxd_रेजिस्टर_group_devices(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i, j, rc;

	क्रम (i = 0; i < idxd->max_groups; i++) अणु
		काष्ठा idxd_group *group = idxd->groups[i];

		rc = device_add(&group->conf_dev);
		अगर (rc < 0)
			जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	j = i - 1;
	क्रम (; i < idxd->max_groups; i++)
		put_device(&idxd->groups[i]->conf_dev);

	जबतक (j--)
		device_unरेजिस्टर(&idxd->groups[j]->conf_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक idxd_रेजिस्टर_wq_devices(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i, rc, j;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		rc = device_add(&wq->conf_dev);
		अगर (rc < 0)
			जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	j = i - 1;
	क्रम (; i < idxd->max_wqs; i++)
		put_device(&idxd->wqs[i]->conf_dev);

	जबतक (j--)
		device_unरेजिस्टर(&idxd->wqs[j]->conf_dev);
	वापस rc;
पूर्ण

पूर्णांक idxd_रेजिस्टर_devices(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक rc, i;

	rc = device_add(&idxd->conf_dev);
	अगर (rc < 0)
		वापस rc;

	rc = idxd_रेजिस्टर_wq_devices(idxd);
	अगर (rc < 0) अणु
		dev_dbg(dev, "WQ devices registering failed: %d\n", rc);
		जाओ err_wq;
	पूर्ण

	rc = idxd_रेजिस्टर_engine_devices(idxd);
	अगर (rc < 0) अणु
		dev_dbg(dev, "Engine devices registering failed: %d\n", rc);
		जाओ err_engine;
	पूर्ण

	rc = idxd_रेजिस्टर_group_devices(idxd);
	अगर (rc < 0) अणु
		dev_dbg(dev, "Group device registering failed: %d\n", rc);
		जाओ err_group;
	पूर्ण

	वापस 0;

 err_group:
	क्रम (i = 0; i < idxd->max_engines; i++)
		device_unरेजिस्टर(&idxd->engines[i]->conf_dev);
 err_engine:
	क्रम (i = 0; i < idxd->max_wqs; i++)
		device_unरेजिस्टर(&idxd->wqs[i]->conf_dev);
 err_wq:
	device_del(&idxd->conf_dev);
	वापस rc;
पूर्ण

व्योम idxd_unरेजिस्टर_devices(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		device_unरेजिस्टर(&wq->conf_dev);
	पूर्ण

	क्रम (i = 0; i < idxd->max_engines; i++) अणु
		काष्ठा idxd_engine *engine = idxd->engines[i];

		device_unरेजिस्टर(&engine->conf_dev);
	पूर्ण

	क्रम (i = 0; i < idxd->max_groups; i++) अणु
		काष्ठा idxd_group *group = idxd->groups[i];

		device_unरेजिस्टर(&group->conf_dev);
	पूर्ण

	device_unरेजिस्टर(&idxd->conf_dev);
पूर्ण

पूर्णांक idxd_रेजिस्टर_bus_type(व्योम)
अणु
	वापस bus_रेजिस्टर(&dsa_bus_type);
पूर्ण

व्योम idxd_unरेजिस्टर_bus_type(व्योम)
अणु
	bus_unरेजिस्टर(&dsa_bus_type);
पूर्ण
