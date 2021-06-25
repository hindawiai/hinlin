<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vDPA bus.
 *
 * Copyright (c) 2020, Red Hat. All rights reserved.
 *     Author: Jason Wang <jasowang@redhat.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/vdpa.h>
#समावेश <uapi/linux/vdpa.h>
#समावेश <net/genetlink.h>
#समावेश <linux/mod_devicetable.h>

अटल LIST_HEAD(mdev_head);
/* A global mutex that protects vdpa management device and device level operations. */
अटल DEFINE_MUTEX(vdpa_dev_mutex);
अटल DEFINE_IDA(vdpa_index_ida);

अटल काष्ठा genl_family vdpa_nl_family;

अटल पूर्णांक vdpa_dev_probe(काष्ठा device *d)
अणु
	काष्ठा vdpa_device *vdev = dev_to_vdpa(d);
	काष्ठा vdpa_driver *drv = drv_to_vdpa(vdev->dev.driver);
	पूर्णांक ret = 0;

	अगर (drv && drv->probe)
		ret = drv->probe(vdev);

	वापस ret;
पूर्ण

अटल पूर्णांक vdpa_dev_हटाओ(काष्ठा device *d)
अणु
	काष्ठा vdpa_device *vdev = dev_to_vdpa(d);
	काष्ठा vdpa_driver *drv = drv_to_vdpa(vdev->dev.driver);

	अगर (drv && drv->हटाओ)
		drv->हटाओ(vdev);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type vdpa_bus = अणु
	.name  = "vdpa",
	.probe = vdpa_dev_probe,
	.हटाओ = vdpa_dev_हटाओ,
पूर्ण;

अटल व्योम vdpa_release_dev(काष्ठा device *d)
अणु
	काष्ठा vdpa_device *vdev = dev_to_vdpa(d);
	स्थिर काष्ठा vdpa_config_ops *ops = vdev->config;

	अगर (ops->मुक्त)
		ops->मुक्त(vdev);

	ida_simple_हटाओ(&vdpa_index_ida, vdev->index);
	kमुक्त(vdev);
पूर्ण

/**
 * __vdpa_alloc_device - allocate and initilaize a vDPA device
 * This allows driver to some prepartion after device is
 * initialized but beक्रमe रेजिस्टरed.
 * @parent: the parent device
 * @config: the bus operations that is supported by this device
 * @size: size of the parent काष्ठाure that contains निजी data
 * @name: name of the vdpa device; optional.
 *
 * Driver should use vdpa_alloc_device() wrapper macro instead of
 * using this directly.
 *
 * Return: Returns an error when parent/config/dma_dev is not set or fail to get
 *	   ida.
 */
काष्ठा vdpa_device *__vdpa_alloc_device(काष्ठा device *parent,
					स्थिर काष्ठा vdpa_config_ops *config,
					माप_प्रकार size, स्थिर अक्षर *name)
अणु
	काष्ठा vdpa_device *vdev;
	पूर्णांक err = -EINVAL;

	अगर (!config)
		जाओ err;

	अगर (!!config->dma_map != !!config->dma_unmap)
		जाओ err;

	err = -ENOMEM;
	vdev = kzalloc(size, GFP_KERNEL);
	अगर (!vdev)
		जाओ err;

	err = ida_alloc(&vdpa_index_ida, GFP_KERNEL);
	अगर (err < 0)
		जाओ err_ida;

	vdev->dev.bus = &vdpa_bus;
	vdev->dev.parent = parent;
	vdev->dev.release = vdpa_release_dev;
	vdev->index = err;
	vdev->config = config;
	vdev->features_valid = false;

	अगर (name)
		err = dev_set_name(&vdev->dev, "%s", name);
	अन्यथा
		err = dev_set_name(&vdev->dev, "vdpa%u", vdev->index);
	अगर (err)
		जाओ err_name;

	device_initialize(&vdev->dev);

	वापस vdev;

err_name:
	ida_simple_हटाओ(&vdpa_index_ida, vdev->index);
err_ida:
	kमुक्त(vdev);
err:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(__vdpa_alloc_device);

अटल पूर्णांक vdpa_name_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा vdpa_device *vdev = container_of(dev, काष्ठा vdpa_device, dev);

	वापस (म_भेद(dev_name(&vdev->dev), data) == 0);
पूर्ण

अटल पूर्णांक __vdpa_रेजिस्टर_device(काष्ठा vdpa_device *vdev, पूर्णांक nvqs)
अणु
	काष्ठा device *dev;

	vdev->nvqs = nvqs;

	lockdep_निश्चित_held(&vdpa_dev_mutex);
	dev = bus_find_device(&vdpa_bus, शून्य, dev_name(&vdev->dev), vdpa_name_match);
	अगर (dev) अणु
		put_device(dev);
		वापस -EEXIST;
	पूर्ण
	वापस device_add(&vdev->dev);
पूर्ण

/**
 * _vdpa_रेजिस्टर_device - रेजिस्टर a vDPA device with vdpa lock held
 * Caller must have a succeed call of vdpa_alloc_device() beक्रमe.
 * Caller must invoke this routine in the management device dev_add()
 * callback after setting up valid mgmtdev क्रम this vdpa device.
 * @vdev: the vdpa device to be रेजिस्टरed to vDPA bus
 * @nvqs: number of virtqueues supported by this device
 *
 * Return: Returns an error when fail to add device to vDPA bus
 */
पूर्णांक _vdpa_रेजिस्टर_device(काष्ठा vdpa_device *vdev, पूर्णांक nvqs)
अणु
	अगर (!vdev->mdev)
		वापस -EINVAL;

	वापस __vdpa_रेजिस्टर_device(vdev, nvqs);
पूर्ण
EXPORT_SYMBOL_GPL(_vdpa_रेजिस्टर_device);

/**
 * vdpa_रेजिस्टर_device - रेजिस्टर a vDPA device
 * Callers must have a succeed call of vdpa_alloc_device() beक्रमe.
 * @vdev: the vdpa device to be रेजिस्टरed to vDPA bus
 * @nvqs: number of virtqueues supported by this device
 *
 * Return: Returns an error when fail to add to vDPA bus
 */
पूर्णांक vdpa_रेजिस्टर_device(काष्ठा vdpa_device *vdev, पूर्णांक nvqs)
अणु
	पूर्णांक err;

	mutex_lock(&vdpa_dev_mutex);
	err = __vdpa_रेजिस्टर_device(vdev, nvqs);
	mutex_unlock(&vdpa_dev_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vdpa_रेजिस्टर_device);

/**
 * _vdpa_unरेजिस्टर_device - unरेजिस्टर a vDPA device
 * Caller must invoke this routine as part of management device dev_del()
 * callback.
 * @vdev: the vdpa device to be unregisted from vDPA bus
 */
व्योम _vdpa_unरेजिस्टर_device(काष्ठा vdpa_device *vdev)
अणु
	lockdep_निश्चित_held(&vdpa_dev_mutex);
	WARN_ON(!vdev->mdev);
	device_unरेजिस्टर(&vdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(_vdpa_unरेजिस्टर_device);

/**
 * vdpa_unरेजिस्टर_device - unरेजिस्टर a vDPA device
 * @vdev: the vdpa device to be unregisted from vDPA bus
 */
व्योम vdpa_unरेजिस्टर_device(काष्ठा vdpa_device *vdev)
अणु
	mutex_lock(&vdpa_dev_mutex);
	device_unरेजिस्टर(&vdev->dev);
	mutex_unlock(&vdpa_dev_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(vdpa_unरेजिस्टर_device);

/**
 * __vdpa_रेजिस्टर_driver - रेजिस्टर a vDPA device driver
 * @drv: the vdpa device driver to be रेजिस्टरed
 * @owner: module owner of the driver
 *
 * Return: Returns an err when fail to करो the registration
 */
पूर्णांक __vdpa_रेजिस्टर_driver(काष्ठा vdpa_driver *drv, काष्ठा module *owner)
अणु
	drv->driver.bus = &vdpa_bus;
	drv->driver.owner = owner;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__vdpa_रेजिस्टर_driver);

/**
 * vdpa_unरेजिस्टर_driver - unरेजिस्टर a vDPA device driver
 * @drv: the vdpa device driver to be unरेजिस्टरed
 */
व्योम vdpa_unरेजिस्टर_driver(काष्ठा vdpa_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(vdpa_unरेजिस्टर_driver);

/**
 * vdpa_mgmtdev_रेजिस्टर - रेजिस्टर a vdpa management device
 *
 * @mdev: Poपूर्णांकer to vdpa management device
 * vdpa_mgmtdev_रेजिस्टर() रेजिस्टर a vdpa management device which supports
 * vdpa device management.
 * Return: Returns 0 on success or failure when required callback ops are not
 *         initialized.
 */
पूर्णांक vdpa_mgmtdev_रेजिस्टर(काष्ठा vdpa_mgmt_dev *mdev)
अणु
	अगर (!mdev->device || !mdev->ops || !mdev->ops->dev_add || !mdev->ops->dev_del)
		वापस -EINVAL;

	INIT_LIST_HEAD(&mdev->list);
	mutex_lock(&vdpa_dev_mutex);
	list_add_tail(&mdev->list, &mdev_head);
	mutex_unlock(&vdpa_dev_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vdpa_mgmtdev_रेजिस्टर);

अटल पूर्णांक vdpa_match_हटाओ(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा vdpa_device *vdev = container_of(dev, काष्ठा vdpa_device, dev);
	काष्ठा vdpa_mgmt_dev *mdev = vdev->mdev;

	अगर (mdev == data)
		mdev->ops->dev_del(mdev, vdev);
	वापस 0;
पूर्ण

व्योम vdpa_mgmtdev_unरेजिस्टर(काष्ठा vdpa_mgmt_dev *mdev)
अणु
	mutex_lock(&vdpa_dev_mutex);

	list_del(&mdev->list);

	/* Filter out all the entries beदीर्घ to this management device and delete it. */
	bus_क्रम_each_dev(&vdpa_bus, शून्य, mdev, vdpa_match_हटाओ);

	mutex_unlock(&vdpa_dev_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(vdpa_mgmtdev_unरेजिस्टर);

अटल bool mgmtdev_handle_match(स्थिर काष्ठा vdpa_mgmt_dev *mdev,
				 स्थिर अक्षर *busname, स्थिर अक्षर *devname)
अणु
	/* Bus name is optional क्रम simulated management device, so ignore the
	 * device with bus अगर bus attribute is provided.
	 */
	अगर ((busname && !mdev->device->bus) || (!busname && mdev->device->bus))
		वापस false;

	अगर (!busname && म_भेद(dev_name(mdev->device), devname) == 0)
		वापस true;

	अगर (busname && (म_भेद(mdev->device->bus->name, busname) == 0) &&
	    (म_भेद(dev_name(mdev->device), devname) == 0))
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा vdpa_mgmt_dev *vdpa_mgmtdev_get_from_attr(काष्ठा nlattr **attrs)
अणु
	काष्ठा vdpa_mgmt_dev *mdev;
	स्थिर अक्षर *busname = शून्य;
	स्थिर अक्षर *devname;

	अगर (!attrs[VDPA_ATTR_MGMTDEV_DEV_NAME])
		वापस ERR_PTR(-EINVAL);
	devname = nla_data(attrs[VDPA_ATTR_MGMTDEV_DEV_NAME]);
	अगर (attrs[VDPA_ATTR_MGMTDEV_BUS_NAME])
		busname = nla_data(attrs[VDPA_ATTR_MGMTDEV_BUS_NAME]);

	list_क्रम_each_entry(mdev, &mdev_head, list) अणु
		अगर (mgmtdev_handle_match(mdev, busname, devname))
			वापस mdev;
	पूर्ण
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक vdpa_nl_mgmtdev_handle_fill(काष्ठा sk_buff *msg, स्थिर काष्ठा vdpa_mgmt_dev *mdev)
अणु
	अगर (mdev->device->bus &&
	    nla_put_string(msg, VDPA_ATTR_MGMTDEV_BUS_NAME, mdev->device->bus->name))
		वापस -EMSGSIZE;
	अगर (nla_put_string(msg, VDPA_ATTR_MGMTDEV_DEV_NAME, dev_name(mdev->device)))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक vdpa_mgmtdev_fill(स्थिर काष्ठा vdpa_mgmt_dev *mdev, काष्ठा sk_buff *msg,
			     u32 portid, u32 seq, पूर्णांक flags)
अणु
	u64 supported_classes = 0;
	व्योम *hdr;
	पूर्णांक i = 0;
	पूर्णांक err;

	hdr = genlmsg_put(msg, portid, seq, &vdpa_nl_family, flags, VDPA_CMD_MGMTDEV_NEW);
	अगर (!hdr)
		वापस -EMSGSIZE;
	err = vdpa_nl_mgmtdev_handle_fill(msg, mdev);
	अगर (err)
		जाओ msg_err;

	जबतक (mdev->id_table[i].device) अणु
		supported_classes |= BIT(mdev->id_table[i].device);
		i++;
	पूर्ण

	अगर (nla_put_u64_64bit(msg, VDPA_ATTR_MGMTDEV_SUPPORTED_CLASSES,
			      supported_classes, VDPA_ATTR_UNSPEC)) अणु
		err = -EMSGSIZE;
		जाओ msg_err;
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस 0;

msg_err:
	genlmsg_cancel(msg, hdr);
	वापस err;
पूर्ण

अटल पूर्णांक vdpa_nl_cmd_mgmtdev_get_करोit(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा vdpa_mgmt_dev *mdev;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	mutex_lock(&vdpa_dev_mutex);
	mdev = vdpa_mgmtdev_get_from_attr(info->attrs);
	अगर (IS_ERR(mdev)) अणु
		mutex_unlock(&vdpa_dev_mutex);
		NL_SET_ERR_MSG_MOD(info->extack, "Fail to find the specified mgmt device");
		err = PTR_ERR(mdev);
		जाओ out;
	पूर्ण

	err = vdpa_mgmtdev_fill(mdev, msg, info->snd_portid, info->snd_seq, 0);
	mutex_unlock(&vdpa_dev_mutex);
	अगर (err)
		जाओ out;
	err = genlmsg_reply(msg, info);
	वापस err;

out:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक
vdpa_nl_cmd_mgmtdev_get_dumpit(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा vdpa_mgmt_dev *mdev;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&vdpa_dev_mutex);
	list_क्रम_each_entry(mdev, &mdev_head, list) अणु
		अगर (idx < start) अणु
			idx++;
			जारी;
		पूर्ण
		err = vdpa_mgmtdev_fill(mdev, msg, NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq, NLM_F_MULTI);
		अगर (err)
			जाओ out;
		idx++;
	पूर्ण
out:
	mutex_unlock(&vdpa_dev_mutex);
	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक vdpa_nl_cmd_dev_add_set_करोit(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा vdpa_mgmt_dev *mdev;
	स्थिर अक्षर *name;
	पूर्णांक err = 0;

	अगर (!info->attrs[VDPA_ATTR_DEV_NAME])
		वापस -EINVAL;

	name = nla_data(info->attrs[VDPA_ATTR_DEV_NAME]);

	mutex_lock(&vdpa_dev_mutex);
	mdev = vdpa_mgmtdev_get_from_attr(info->attrs);
	अगर (IS_ERR(mdev)) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Fail to find the specified management device");
		err = PTR_ERR(mdev);
		जाओ err;
	पूर्ण

	err = mdev->ops->dev_add(mdev, name);
err:
	mutex_unlock(&vdpa_dev_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक vdpa_nl_cmd_dev_del_set_करोit(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा vdpa_mgmt_dev *mdev;
	काष्ठा vdpa_device *vdev;
	काष्ठा device *dev;
	स्थिर अक्षर *name;
	पूर्णांक err = 0;

	अगर (!info->attrs[VDPA_ATTR_DEV_NAME])
		वापस -EINVAL;
	name = nla_data(info->attrs[VDPA_ATTR_DEV_NAME]);

	mutex_lock(&vdpa_dev_mutex);
	dev = bus_find_device(&vdpa_bus, शून्य, name, vdpa_name_match);
	अगर (!dev) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "device not found");
		err = -ENODEV;
		जाओ dev_err;
	पूर्ण
	vdev = container_of(dev, काष्ठा vdpa_device, dev);
	अगर (!vdev->mdev) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Only user created device can be deleted by user");
		err = -EINVAL;
		जाओ mdev_err;
	पूर्ण
	mdev = vdev->mdev;
	mdev->ops->dev_del(mdev, vdev);
mdev_err:
	put_device(dev);
dev_err:
	mutex_unlock(&vdpa_dev_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक
vdpa_dev_fill(काष्ठा vdpa_device *vdev, काष्ठा sk_buff *msg, u32 portid, u32 seq,
	      पूर्णांक flags, काष्ठा netlink_ext_ack *extack)
अणु
	u16 max_vq_size;
	u32 device_id;
	u32 venकरोr_id;
	व्योम *hdr;
	पूर्णांक err;

	hdr = genlmsg_put(msg, portid, seq, &vdpa_nl_family, flags, VDPA_CMD_DEV_NEW);
	अगर (!hdr)
		वापस -EMSGSIZE;

	err = vdpa_nl_mgmtdev_handle_fill(msg, vdev->mdev);
	अगर (err)
		जाओ msg_err;

	device_id = vdev->config->get_device_id(vdev);
	venकरोr_id = vdev->config->get_venकरोr_id(vdev);
	max_vq_size = vdev->config->get_vq_num_max(vdev);

	err = -EMSGSIZE;
	अगर (nla_put_string(msg, VDPA_ATTR_DEV_NAME, dev_name(&vdev->dev)))
		जाओ msg_err;
	अगर (nla_put_u32(msg, VDPA_ATTR_DEV_ID, device_id))
		जाओ msg_err;
	अगर (nla_put_u32(msg, VDPA_ATTR_DEV_VENDOR_ID, venकरोr_id))
		जाओ msg_err;
	अगर (nla_put_u32(msg, VDPA_ATTR_DEV_MAX_VQS, vdev->nvqs))
		जाओ msg_err;
	अगर (nla_put_u16(msg, VDPA_ATTR_DEV_MAX_VQ_SIZE, max_vq_size))
		जाओ msg_err;

	genlmsg_end(msg, hdr);
	वापस 0;

msg_err:
	genlmsg_cancel(msg, hdr);
	वापस err;
पूर्ण

अटल पूर्णांक vdpa_nl_cmd_dev_get_करोit(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा vdpa_device *vdev;
	काष्ठा sk_buff *msg;
	स्थिर अक्षर *devname;
	काष्ठा device *dev;
	पूर्णांक err;

	अगर (!info->attrs[VDPA_ATTR_DEV_NAME])
		वापस -EINVAL;
	devname = nla_data(info->attrs[VDPA_ATTR_DEV_NAME]);
	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	mutex_lock(&vdpa_dev_mutex);
	dev = bus_find_device(&vdpa_bus, शून्य, devname, vdpa_name_match);
	अगर (!dev) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "device not found");
		err = -ENODEV;
		जाओ err;
	पूर्ण
	vdev = container_of(dev, काष्ठा vdpa_device, dev);
	अगर (!vdev->mdev) अणु
		err = -EINVAL;
		जाओ mdev_err;
	पूर्ण
	err = vdpa_dev_fill(vdev, msg, info->snd_portid, info->snd_seq, 0, info->extack);
	अगर (!err)
		err = genlmsg_reply(msg, info);
mdev_err:
	put_device(dev);
err:
	mutex_unlock(&vdpa_dev_mutex);
	अगर (err)
		nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

काष्ठा vdpa_dev_dump_info अणु
	काष्ठा sk_buff *msg;
	काष्ठा netlink_callback *cb;
	पूर्णांक start_idx;
	पूर्णांक idx;
पूर्ण;

अटल पूर्णांक vdpa_dev_dump(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा vdpa_device *vdev = container_of(dev, काष्ठा vdpa_device, dev);
	काष्ठा vdpa_dev_dump_info *info = data;
	पूर्णांक err;

	अगर (!vdev->mdev)
		वापस 0;
	अगर (info->idx < info->start_idx) अणु
		info->idx++;
		वापस 0;
	पूर्ण
	err = vdpa_dev_fill(vdev, info->msg, NETLINK_CB(info->cb->skb).portid,
			    info->cb->nlh->nlmsg_seq, NLM_F_MULTI, info->cb->extack);
	अगर (err)
		वापस err;

	info->idx++;
	वापस 0;
पूर्ण

अटल पूर्णांक vdpa_nl_cmd_dev_get_dumpit(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा vdpa_dev_dump_info info;

	info.msg = msg;
	info.cb = cb;
	info.start_idx = cb->args[0];
	info.idx = 0;

	mutex_lock(&vdpa_dev_mutex);
	bus_क्रम_each_dev(&vdpa_bus, शून्य, &info, vdpa_dev_dump);
	mutex_unlock(&vdpa_dev_mutex);
	cb->args[0] = info.idx;
	वापस msg->len;
पूर्ण

अटल स्थिर काष्ठा nla_policy vdpa_nl_policy[VDPA_ATTR_MAX + 1] = अणु
	[VDPA_ATTR_MGMTDEV_BUS_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[VDPA_ATTR_MGMTDEV_DEV_NAME] = अणु .type = NLA_STRING पूर्ण,
	[VDPA_ATTR_DEV_NAME] = अणु .type = NLA_STRING पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_ops vdpa_nl_ops[] = अणु
	अणु
		.cmd = VDPA_CMD_MGMTDEV_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = vdpa_nl_cmd_mgmtdev_get_करोit,
		.dumpit = vdpa_nl_cmd_mgmtdev_get_dumpit,
	पूर्ण,
	अणु
		.cmd = VDPA_CMD_DEV_NEW,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = vdpa_nl_cmd_dev_add_set_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = VDPA_CMD_DEV_DEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = vdpa_nl_cmd_dev_del_set_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = VDPA_CMD_DEV_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = vdpa_nl_cmd_dev_get_करोit,
		.dumpit = vdpa_nl_cmd_dev_get_dumpit,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family vdpa_nl_family __ro_after_init = अणु
	.name = VDPA_GENL_NAME,
	.version = VDPA_GENL_VERSION,
	.maxattr = VDPA_ATTR_MAX,
	.policy = vdpa_nl_policy,
	.netnsok = false,
	.module = THIS_MODULE,
	.ops = vdpa_nl_ops,
	.n_ops = ARRAY_SIZE(vdpa_nl_ops),
पूर्ण;

अटल पूर्णांक vdpa_init(व्योम)
अणु
	पूर्णांक err;

	err = bus_रेजिस्टर(&vdpa_bus);
	अगर (err)
		वापस err;
	err = genl_रेजिस्टर_family(&vdpa_nl_family);
	अगर (err)
		जाओ err;
	वापस 0;

err:
	bus_unरेजिस्टर(&vdpa_bus);
	वापस err;
पूर्ण

अटल व्योम __निकास vdpa_निकास(व्योम)
अणु
	genl_unरेजिस्टर_family(&vdpa_nl_family);
	bus_unरेजिस्टर(&vdpa_bus);
	ida_destroy(&vdpa_index_ida);
पूर्ण
core_initcall(vdpa_init);
module_निकास(vdpa_निकास);

MODULE_AUTHOR("Jason Wang <jasowang@redhat.com>");
MODULE_LICENSE("GPL v2");
