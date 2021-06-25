<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * remote processor messaging bus
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>

#समावेश "rpmsg_internal.h"

/**
 * rpmsg_create_channel() - create a new rpmsg channel
 * using its name and address info.
 * @rpdev: rpmsg device
 * @chinfo: channel_info to bind
 *
 * Returns a poपूर्णांकer to the new rpmsg device on success, or शून्य on error.
 */
काष्ठा rpmsg_device *rpmsg_create_channel(काष्ठा rpmsg_device *rpdev,
					  काष्ठा rpmsg_channel_info *chinfo)
अणु
	अगर (WARN_ON(!rpdev))
		वापस शून्य;
	अगर (!rpdev->ops || !rpdev->ops->create_channel) अणु
		dev_err(&rpdev->dev, "no create_channel ops found\n");
		वापस शून्य;
	पूर्ण

	वापस rpdev->ops->create_channel(rpdev, chinfo);
पूर्ण
EXPORT_SYMBOL(rpmsg_create_channel);

/**
 * rpmsg_release_channel() - release a rpmsg channel
 * using its name and address info.
 * @rpdev: rpmsg device
 * @chinfo: channel_info to bind
 *
 * Returns 0 on success or an appropriate error value.
 */
पूर्णांक rpmsg_release_channel(काष्ठा rpmsg_device *rpdev,
			  काष्ठा rpmsg_channel_info *chinfo)
अणु
	अगर (WARN_ON(!rpdev))
		वापस -EINVAL;
	अगर (!rpdev->ops || !rpdev->ops->release_channel) अणु
		dev_err(&rpdev->dev, "no release_channel ops found\n");
		वापस -ENXIO;
	पूर्ण

	वापस rpdev->ops->release_channel(rpdev, chinfo);
पूर्ण
EXPORT_SYMBOL(rpmsg_release_channel);

/**
 * rpmsg_create_ept() - create a new rpmsg_endpoपूर्णांक
 * @rpdev: rpmsg channel device
 * @cb: rx callback handler
 * @priv: निजी data क्रम the driver's use
 * @chinfo: channel_info with the local rpmsg address to bind with @cb
 *
 * Every rpmsg address in the प्रणाली is bound to an rx callback (so when
 * inbound messages arrive, they are dispatched by the rpmsg bus using the
 * appropriate callback handler) by means of an rpmsg_endpoपूर्णांक काष्ठा.
 *
 * This function allows drivers to create such an endpoपूर्णांक, and by that,
 * bind a callback, and possibly some निजी data too, to an rpmsg address
 * (either one that is known in advance, or one that will be dynamically
 * asचिन्हित क्रम them).
 *
 * Simple rpmsg drivers need not call rpmsg_create_ept, because an endpoपूर्णांक
 * is alपढ़ोy created क्रम them when they are probed by the rpmsg bus
 * (using the rx callback provided when they रेजिस्टरed to the rpmsg bus).
 *
 * So things should just work क्रम simple drivers: they alपढ़ोy have an
 * endpoपूर्णांक, their rx callback is bound to their rpmsg address, and when
 * relevant inbound messages arrive (i.e. messages which their dst address
 * equals to the src address of their rpmsg channel), the driver's handler
 * is invoked to process it.
 *
 * That said, more complicated drivers might need to allocate
 * additional rpmsg addresses, and bind them to dअगरferent rx callbacks.
 * To accomplish that, those drivers need to call this function.
 *
 * Drivers should provide their @rpdev channel (so the new endpoपूर्णांक would beदीर्घ
 * to the same remote processor their channel beदीर्घs to), an rx callback
 * function, an optional निजी data (which is provided back when the
 * rx callback is invoked), and an address they want to bind with the
 * callback. If @addr is RPMSG_ADDR_ANY, then rpmsg_create_ept will
 * dynamically assign them an available rpmsg address (drivers should have
 * a very good reason why not to always use RPMSG_ADDR_ANY here).
 *
 * Returns a poपूर्णांकer to the endpoपूर्णांक on success, or शून्य on error.
 */
काष्ठा rpmsg_endpoपूर्णांक *rpmsg_create_ept(काष्ठा rpmsg_device *rpdev,
					rpmsg_rx_cb_t cb, व्योम *priv,
					काष्ठा rpmsg_channel_info chinfo)
अणु
	अगर (WARN_ON(!rpdev))
		वापस शून्य;

	वापस rpdev->ops->create_ept(rpdev, cb, priv, chinfo);
पूर्ण
EXPORT_SYMBOL(rpmsg_create_ept);

/**
 * rpmsg_destroy_ept() - destroy an existing rpmsg endpoपूर्णांक
 * @ept: endpoing to destroy
 *
 * Should be used by drivers to destroy an rpmsg endpoपूर्णांक previously
 * created with rpmsg_create_ept(). As with other types of "free" शून्य
 * is a valid parameter.
 */
व्योम rpmsg_destroy_ept(काष्ठा rpmsg_endpoपूर्णांक *ept)
अणु
	अगर (ept && ept->ops)
		ept->ops->destroy_ept(ept);
पूर्ण
EXPORT_SYMBOL(rpmsg_destroy_ept);

/**
 * rpmsg_send() - send a message across to the remote processor
 * @ept: the rpmsg endpoपूर्णांक
 * @data: payload of message
 * @len: length of payload
 *
 * This function sends @data of length @len on the @ept endpoपूर्णांक.
 * The message will be sent to the remote processor which the @ept
 * endpoपूर्णांक beदीर्घs to, using @ept's address and its associated rpmsg
 * device destination addresses.
 * In हाल there are no TX buffers available, the function will block until
 * one becomes available, or a समयout of 15 seconds elapses. When the latter
 * happens, -ERESTARTSYS is वापसed.
 *
 * Can only be called from process context (क्रम now).
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
पूर्णांक rpmsg_send(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	अगर (WARN_ON(!ept))
		वापस -EINVAL;
	अगर (!ept->ops->send)
		वापस -ENXIO;

	वापस ept->ops->send(ept, data, len);
पूर्ण
EXPORT_SYMBOL(rpmsg_send);

/**
 * rpmsg_sendto() - send a message across to the remote processor, specअगरy dst
 * @ept: the rpmsg endpoपूर्णांक
 * @data: payload of message
 * @len: length of payload
 * @dst: destination address
 *
 * This function sends @data of length @len to the remote @dst address.
 * The message will be sent to the remote processor which the @ept
 * endpoपूर्णांक beदीर्घs to, using @ept's address as source.
 * In हाल there are no TX buffers available, the function will block until
 * one becomes available, or a समयout of 15 seconds elapses. When the latter
 * happens, -ERESTARTSYS is वापसed.
 *
 * Can only be called from process context (क्रम now).
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
पूर्णांक rpmsg_sendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst)
अणु
	अगर (WARN_ON(!ept))
		वापस -EINVAL;
	अगर (!ept->ops->sendto)
		वापस -ENXIO;

	वापस ept->ops->sendto(ept, data, len, dst);
पूर्ण
EXPORT_SYMBOL(rpmsg_sendto);

/**
 * rpmsg_send_offchannel() - send a message using explicit src/dst addresses
 * @ept: the rpmsg endpoपूर्णांक
 * @src: source address
 * @dst: destination address
 * @data: payload of message
 * @len: length of payload
 *
 * This function sends @data of length @len to the remote @dst address,
 * and uses @src as the source address.
 * The message will be sent to the remote processor which the @ept
 * endpoपूर्णांक beदीर्घs to.
 * In हाल there are no TX buffers available, the function will block until
 * one becomes available, or a समयout of 15 seconds elapses. When the latter
 * happens, -ERESTARTSYS is वापसed.
 *
 * Can only be called from process context (क्रम now).
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
पूर्णांक rpmsg_send_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src, u32 dst,
			  व्योम *data, पूर्णांक len)
अणु
	अगर (WARN_ON(!ept))
		वापस -EINVAL;
	अगर (!ept->ops->send_offchannel)
		वापस -ENXIO;

	वापस ept->ops->send_offchannel(ept, src, dst, data, len);
पूर्ण
EXPORT_SYMBOL(rpmsg_send_offchannel);

/**
 * rpmsg_trysend() - send a message across to the remote processor
 * @ept: the rpmsg endpoपूर्णांक
 * @data: payload of message
 * @len: length of payload
 *
 * This function sends @data of length @len on the @ept endpoपूर्णांक.
 * The message will be sent to the remote processor which the @ept
 * endpoपूर्णांक beदीर्घs to, using @ept's address as source and its associated
 * rpdev's address as destination.
 * In हाल there are no TX buffers available, the function will immediately
 * वापस -ENOMEM without रुकोing until one becomes available.
 *
 * Can only be called from process context (क्रम now).
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
पूर्णांक rpmsg_trysend(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	अगर (WARN_ON(!ept))
		वापस -EINVAL;
	अगर (!ept->ops->trysend)
		वापस -ENXIO;

	वापस ept->ops->trysend(ept, data, len);
पूर्ण
EXPORT_SYMBOL(rpmsg_trysend);

/**
 * rpmsg_trysendto() - send a message across to the remote processor, specअगरy dst
 * @ept: the rpmsg endpoपूर्णांक
 * @data: payload of message
 * @len: length of payload
 * @dst: destination address
 *
 * This function sends @data of length @len to the remote @dst address.
 * The message will be sent to the remote processor which the @ept
 * endpoपूर्णांक beदीर्घs to, using @ept's address as source.
 * In हाल there are no TX buffers available, the function will immediately
 * वापस -ENOMEM without रुकोing until one becomes available.
 *
 * Can only be called from process context (क्रम now).
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
पूर्णांक rpmsg_trysendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst)
अणु
	अगर (WARN_ON(!ept))
		वापस -EINVAL;
	अगर (!ept->ops->trysendto)
		वापस -ENXIO;

	वापस ept->ops->trysendto(ept, data, len, dst);
पूर्ण
EXPORT_SYMBOL(rpmsg_trysendto);

/**
 * rpmsg_poll() - poll the endpoपूर्णांक's send buffers
 * @ept:	the rpmsg endpoपूर्णांक
 * @filp:	file क्रम poll_रुको()
 * @रुको:	poll_table क्रम poll_रुको()
 *
 * Returns mask representing the current state of the endpoपूर्णांक's send buffers
 */
__poll_t rpmsg_poll(काष्ठा rpmsg_endpoपूर्णांक *ept, काष्ठा file *filp,
			poll_table *रुको)
अणु
	अगर (WARN_ON(!ept))
		वापस 0;
	अगर (!ept->ops->poll)
		वापस 0;

	वापस ept->ops->poll(ept, filp, रुको);
पूर्ण
EXPORT_SYMBOL(rpmsg_poll);

/**
 * rpmsg_trysend_offchannel() - send a message using explicit src/dst addresses
 * @ept: the rpmsg endpoपूर्णांक
 * @src: source address
 * @dst: destination address
 * @data: payload of message
 * @len: length of payload
 *
 * This function sends @data of length @len to the remote @dst address,
 * and uses @src as the source address.
 * The message will be sent to the remote processor which the @ept
 * endpoपूर्णांक beदीर्घs to.
 * In हाल there are no TX buffers available, the function will immediately
 * वापस -ENOMEM without रुकोing until one becomes available.
 *
 * Can only be called from process context (क्रम now).
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
पूर्णांक rpmsg_trysend_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src, u32 dst,
			     व्योम *data, पूर्णांक len)
अणु
	अगर (WARN_ON(!ept))
		वापस -EINVAL;
	अगर (!ept->ops->trysend_offchannel)
		वापस -ENXIO;

	वापस ept->ops->trysend_offchannel(ept, src, dst, data, len);
पूर्ण
EXPORT_SYMBOL(rpmsg_trysend_offchannel);

/*
 * match a rpmsg channel with a channel info काष्ठा.
 * this is used to make sure we're not creating rpmsg devices क्रम channels
 * that alपढ़ोy exist.
 */
अटल पूर्णांक rpmsg_device_match(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा rpmsg_channel_info *chinfo = data;
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);

	अगर (chinfo->src != RPMSG_ADDR_ANY && chinfo->src != rpdev->src)
		वापस 0;

	अगर (chinfo->dst != RPMSG_ADDR_ANY && chinfo->dst != rpdev->dst)
		वापस 0;

	अगर (म_भेदन(chinfo->name, rpdev->id.name, RPMSG_NAME_SIZE))
		वापस 0;

	/* found a match ! */
	वापस 1;
पूर्ण

काष्ठा device *rpmsg_find_device(काष्ठा device *parent,
				 काष्ठा rpmsg_channel_info *chinfo)
अणु
	वापस device_find_child(parent, chinfo, rpmsg_device_match);

पूर्ण
EXPORT_SYMBOL(rpmsg_find_device);

/* sysfs show configuration fields */
#घोषणा rpmsg_show_attr(field, path, क्रमmat_string)			\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev,					\
			काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);		\
									\
	वापस प्र_लिखो(buf, क्रमmat_string, rpdev->path);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(field);

#घोषणा rpmsg_string_attr(field, member)				\
अटल sमाप_प्रकार								\
field##_store(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
	      स्थिर अक्षर *buf, माप_प्रकार sz)				\
अणु									\
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);		\
	अक्षर *new, *old;						\
									\
	new = kstrndup(buf, sz, GFP_KERNEL);				\
	अगर (!new)							\
		वापस -ENOMEM;						\
	new[म_खोज(new, "\n")] = '\0';					\
									\
	device_lock(dev);						\
	old = rpdev->member;						\
	अगर (म_माप(new)) अणु						\
		rpdev->member = new;					\
	पूर्ण अन्यथा अणु							\
		kमुक्त(new);						\
		rpdev->member = शून्य;					\
	पूर्ण								\
	device_unlock(dev);						\
									\
	kमुक्त(old);							\
									\
	वापस sz;							\
पूर्ण									\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev,					\
	     काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);		\
									\
	वापस प्र_लिखो(buf, "%s\n", rpdev->member);			\
पूर्ण									\
अटल DEVICE_ATTR_RW(field)

/* क्रम more info, see Documentation/ABI/testing/sysfs-bus-rpmsg */
rpmsg_show_attr(name, id.name, "%s\n");
rpmsg_show_attr(src, src, "0x%x\n");
rpmsg_show_attr(dst, dst, "0x%x\n");
rpmsg_show_attr(announce, announce ? "true" : "false", "%s\n");
rpmsg_string_attr(driver_override, driver_override);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	sमाप_प्रकार len;

	len = of_device_modalias(dev, buf, PAGE_SIZE);
	अगर (len != -ENODEV)
		वापस len;

	वापस प्र_लिखो(buf, RPMSG_DEVICE_MODALIAS_FMT "\n", rpdev->id.name);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *rpmsg_dev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_modalias.attr,
	&dev_attr_dst.attr,
	&dev_attr_src.attr,
	&dev_attr_announce.attr,
	&dev_attr_driver_override.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(rpmsg_dev);

/* rpmsg devices and drivers are matched using the service name */
अटल अंतरभूत पूर्णांक rpmsg_id_match(स्थिर काष्ठा rpmsg_device *rpdev,
				  स्थिर काष्ठा rpmsg_device_id *id)
अणु
	वापस म_भेदन(id->name, rpdev->id.name, RPMSG_NAME_SIZE) == 0;
पूर्ण

/* match rpmsg channel and rpmsg driver */
अटल पूर्णांक rpmsg_dev_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	काष्ठा rpmsg_driver *rpdrv = to_rpmsg_driver(drv);
	स्थिर काष्ठा rpmsg_device_id *ids = rpdrv->id_table;
	अचिन्हित पूर्णांक i;

	अगर (rpdev->driver_override)
		वापस !म_भेद(rpdev->driver_override, drv->name);

	अगर (ids)
		क्रम (i = 0; ids[i].name[0]; i++)
			अगर (rpmsg_id_match(rpdev, &ids[i]))
				वापस 1;

	वापस of_driver_match_device(dev, drv);
पूर्ण

अटल पूर्णांक rpmsg_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	पूर्णांक ret;

	ret = of_device_uevent_modalias(dev, env);
	अगर (ret != -ENODEV)
		वापस ret;

	वापस add_uevent_var(env, "MODALIAS=" RPMSG_DEVICE_MODALIAS_FMT,
					rpdev->id.name);
पूर्ण

/*
 * when an rpmsg driver is probed with a channel, we seamlessly create
 * it an endpoपूर्णांक, binding its rx callback to a unique local rpmsg
 * address.
 *
 * अगर we need to, we also announce about this channel to the remote
 * processor (needed in हाल the driver is exposing an rpmsg service).
 */
अटल पूर्णांक rpmsg_dev_probe(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	काष्ठा rpmsg_driver *rpdrv = to_rpmsg_driver(rpdev->dev.driver);
	काष्ठा rpmsg_channel_info chinfo = अणुपूर्ण;
	काष्ठा rpmsg_endpoपूर्णांक *ept = शून्य;
	पूर्णांक err;

	err = dev_pm_करोमुख्य_attach(dev, true);
	अगर (err)
		जाओ out;

	अगर (rpdrv->callback) अणु
		म_नकलन(chinfo.name, rpdev->id.name, RPMSG_NAME_SIZE);
		chinfo.src = rpdev->src;
		chinfo.dst = RPMSG_ADDR_ANY;

		ept = rpmsg_create_ept(rpdev, rpdrv->callback, शून्य, chinfo);
		अगर (!ept) अणु
			dev_err(dev, "failed to create endpoint\n");
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		rpdev->ept = ept;
		rpdev->src = ept->addr;
	पूर्ण

	err = rpdrv->probe(rpdev);
	अगर (err) अणु
		dev_err(dev, "%s: failed: %d\n", __func__, err);
		अगर (ept)
			rpmsg_destroy_ept(ept);
		जाओ out;
	पूर्ण

	अगर (ept && rpdev->ops->announce_create)
		err = rpdev->ops->announce_create(rpdev);
out:
	वापस err;
पूर्ण

अटल पूर्णांक rpmsg_dev_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	काष्ठा rpmsg_driver *rpdrv = to_rpmsg_driver(rpdev->dev.driver);
	पूर्णांक err = 0;

	अगर (rpdev->ops->announce_destroy)
		err = rpdev->ops->announce_destroy(rpdev);

	अगर (rpdrv->हटाओ)
		rpdrv->हटाओ(rpdev);

	dev_pm_करोमुख्य_detach(dev, true);

	अगर (rpdev->ept)
		rpmsg_destroy_ept(rpdev->ept);

	वापस err;
पूर्ण

अटल काष्ठा bus_type rpmsg_bus = अणु
	.name		= "rpmsg",
	.match		= rpmsg_dev_match,
	.dev_groups	= rpmsg_dev_groups,
	.uevent		= rpmsg_uevent,
	.probe		= rpmsg_dev_probe,
	.हटाओ		= rpmsg_dev_हटाओ,
पूर्ण;

पूर्णांक rpmsg_रेजिस्टर_device(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा device *dev = &rpdev->dev;
	पूर्णांक ret;

	dev_set_name(&rpdev->dev, "%s.%s.%d.%d", dev_name(dev->parent),
		     rpdev->id.name, rpdev->src, rpdev->dst);

	rpdev->dev.bus = &rpmsg_bus;

	ret = device_रेजिस्टर(&rpdev->dev);
	अगर (ret) अणु
		dev_err(dev, "device_register failed: %d\n", ret);
		put_device(&rpdev->dev);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(rpmsg_रेजिस्टर_device);

/*
 * find an existing channel using its name + address properties,
 * and destroy it
 */
पूर्णांक rpmsg_unरेजिस्टर_device(काष्ठा device *parent,
			    काष्ठा rpmsg_channel_info *chinfo)
अणु
	काष्ठा device *dev;

	dev = rpmsg_find_device(parent, chinfo);
	अगर (!dev)
		वापस -EINVAL;

	device_unरेजिस्टर(dev);

	put_device(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rpmsg_unरेजिस्टर_device);

/**
 * __रेजिस्टर_rpmsg_driver() - रेजिस्टर an rpmsg driver with the rpmsg bus
 * @rpdrv: poपूर्णांकer to a काष्ठा rpmsg_driver
 * @owner: owning module/driver
 *
 * Returns 0 on success, and an appropriate error value on failure.
 */
पूर्णांक __रेजिस्टर_rpmsg_driver(काष्ठा rpmsg_driver *rpdrv, काष्ठा module *owner)
अणु
	rpdrv->drv.bus = &rpmsg_bus;
	rpdrv->drv.owner = owner;
	वापस driver_रेजिस्टर(&rpdrv->drv);
पूर्ण
EXPORT_SYMBOL(__रेजिस्टर_rpmsg_driver);

/**
 * unरेजिस्टर_rpmsg_driver() - unरेजिस्टर an rpmsg driver from the rpmsg bus
 * @rpdrv: poपूर्णांकer to a काष्ठा rpmsg_driver
 *
 * Returns 0 on success, and an appropriate error value on failure.
 */
व्योम unरेजिस्टर_rpmsg_driver(काष्ठा rpmsg_driver *rpdrv)
अणु
	driver_unरेजिस्टर(&rpdrv->drv);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_rpmsg_driver);


अटल पूर्णांक __init rpmsg_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&rpmsg_bus);
	अगर (ret)
		pr_err("failed to register rpmsg bus: %d\n", ret);

	वापस ret;
पूर्ण
postcore_initcall(rpmsg_init);

अटल व्योम __निकास rpmsg_fini(व्योम)
अणु
	bus_unरेजिस्टर(&rpmsg_bus);
पूर्ण
module_निकास(rpmsg_fini);

MODULE_DESCRIPTION("remote processor messaging bus");
MODULE_LICENSE("GPL v2");
