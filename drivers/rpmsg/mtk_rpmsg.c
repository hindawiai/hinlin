<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2019 Google LLC.

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/rpmsg/mtk_rpmsg.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "rpmsg_internal.h"

काष्ठा mtk_rpmsg_rproc_subdev अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mtk_rpmsg_info *info;
	काष्ठा rpmsg_endpoपूर्णांक *ns_ept;
	काष्ठा rproc_subdev subdev;

	काष्ठा work_काष्ठा रेजिस्टर_work;
	काष्ठा list_head channels;
	काष्ठा mutex channels_lock;
पूर्ण;

#घोषणा to_mtk_subdev(d) container_of(d, काष्ठा mtk_rpmsg_rproc_subdev, subdev)

काष्ठा mtk_rpmsg_channel_info अणु
	काष्ठा rpmsg_channel_info info;
	bool रेजिस्टरed;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा rpmsg_ns_msg - dynamic name service announcement message
 * @name: name of remote service that is published
 * @addr: address of remote service that is published
 *
 * This message is sent across to publish a new service. When we receive these
 * messages, an appropriate rpmsg channel (i.e device) is created. In turn, the
 * ->probe() handler of the appropriate rpmsg driver will be invoked
 *  (अगर/as-soon-as one is रेजिस्टरed).
 */
काष्ठा rpmsg_ns_msg अणु
	अक्षर name[RPMSG_NAME_SIZE];
	u32 addr;
पूर्ण __packed;

काष्ठा mtk_rpmsg_device अणु
	काष्ठा rpmsg_device rpdev;
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev;
पूर्ण;

काष्ठा mtk_rpmsg_endpoपूर्णांक अणु
	काष्ठा rpmsg_endpoपूर्णांक ept;
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev;
पूर्ण;

#घोषणा to_mtk_rpmsg_device(r) container_of(r, काष्ठा mtk_rpmsg_device, rpdev)
#घोषणा to_mtk_rpmsg_endpoपूर्णांक(r) container_of(r, काष्ठा mtk_rpmsg_endpoपूर्णांक, ept)

अटल स्थिर काष्ठा rpmsg_endpoपूर्णांक_ops mtk_rpmsg_endpoपूर्णांक_ops;

अटल व्योम __mtk_ept_release(काष्ठा kref *kref)
अणु
	काष्ठा rpmsg_endpoपूर्णांक *ept = container_of(kref, काष्ठा rpmsg_endpoपूर्णांक,
						  refcount);
	kमुक्त(to_mtk_rpmsg_endpoपूर्णांक(ept));
पूर्ण

अटल व्योम mtk_rpmsg_ipi_handler(व्योम *data, अचिन्हित पूर्णांक len, व्योम *priv)
अणु
	काष्ठा mtk_rpmsg_endpoपूर्णांक *mept = priv;
	काष्ठा rpmsg_endpoपूर्णांक *ept = &mept->ept;
	पूर्णांक ret;

	ret = (*ept->cb)(ept->rpdev, data, len, ept->priv, ept->addr);
	अगर (ret)
		dev_warn(&ept->rpdev->dev, "rpmsg handler return error = %d",
			 ret);
पूर्ण

अटल काष्ठा rpmsg_endpoपूर्णांक *
__mtk_create_ept(काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev,
		 काष्ठा rpmsg_device *rpdev, rpmsg_rx_cb_t cb, व्योम *priv,
		 u32 id)
अणु
	काष्ठा mtk_rpmsg_endpoपूर्णांक *mept;
	काष्ठा rpmsg_endpoपूर्णांक *ept;
	काष्ठा platक्रमm_device *pdev = mtk_subdev->pdev;
	पूर्णांक ret;

	mept = kzalloc(माप(*mept), GFP_KERNEL);
	अगर (!mept)
		वापस शून्य;
	mept->mtk_subdev = mtk_subdev;

	ept = &mept->ept;
	kref_init(&ept->refcount);

	ept->rpdev = rpdev;
	ept->cb = cb;
	ept->priv = priv;
	ept->ops = &mtk_rpmsg_endpoपूर्णांक_ops;
	ept->addr = id;

	ret = mtk_subdev->info->रेजिस्टर_ipi(pdev, id, mtk_rpmsg_ipi_handler,
					     mept);
	अगर (ret) अणु
		dev_err(&pdev->dev, "IPI register failed, id = %d", id);
		kref_put(&ept->refcount, __mtk_ept_release);
		वापस शून्य;
	पूर्ण

	वापस ept;
पूर्ण

अटल काष्ठा rpmsg_endpoपूर्णांक *
mtk_rpmsg_create_ept(काष्ठा rpmsg_device *rpdev, rpmsg_rx_cb_t cb, व्योम *priv,
		     काष्ठा rpmsg_channel_info chinfo)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev =
		to_mtk_rpmsg_device(rpdev)->mtk_subdev;

	वापस __mtk_create_ept(mtk_subdev, rpdev, cb, priv, chinfo.src);
पूर्ण

अटल व्योम mtk_rpmsg_destroy_ept(काष्ठा rpmsg_endpoपूर्णांक *ept)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev =
		to_mtk_rpmsg_endpoपूर्णांक(ept)->mtk_subdev;

	mtk_subdev->info->unरेजिस्टर_ipi(mtk_subdev->pdev, ept->addr);
	kref_put(&ept->refcount, __mtk_ept_release);
पूर्ण

अटल पूर्णांक mtk_rpmsg_send(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev =
		to_mtk_rpmsg_endpoपूर्णांक(ept)->mtk_subdev;

	वापस mtk_subdev->info->send_ipi(mtk_subdev->pdev, ept->addr, data,
					  len, 0);
पूर्ण

अटल पूर्णांक mtk_rpmsg_trysend(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev =
		to_mtk_rpmsg_endpoपूर्णांक(ept)->mtk_subdev;

	/*
	 * TODO: This currently is same as mtk_rpmsg_send, and रुको until SCP
	 * received the last command.
	 */
	वापस mtk_subdev->info->send_ipi(mtk_subdev->pdev, ept->addr, data,
					  len, 0);
पूर्ण

अटल स्थिर काष्ठा rpmsg_endpoपूर्णांक_ops mtk_rpmsg_endpoपूर्णांक_ops = अणु
	.destroy_ept = mtk_rpmsg_destroy_ept,
	.send = mtk_rpmsg_send,
	.trysend = mtk_rpmsg_trysend,
पूर्ण;

अटल व्योम mtk_rpmsg_release_device(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	काष्ठा mtk_rpmsg_device *mdev = to_mtk_rpmsg_device(rpdev);

	kमुक्त(mdev);
पूर्ण

अटल स्थिर काष्ठा rpmsg_device_ops mtk_rpmsg_device_ops = अणु
	.create_ept = mtk_rpmsg_create_ept,
पूर्ण;

अटल काष्ठा device_node *
mtk_rpmsg_match_device_subnode(काष्ठा device_node *node, स्थिर अक्षर *channel)
अणु
	काष्ठा device_node *child;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	क्रम_each_available_child_of_node(node, child) अणु
		ret = of_property_पढ़ो_string(child, "mtk,rpmsg-name", &name);
		अगर (ret)
			जारी;

		अगर (म_भेद(name, channel) == 0)
			वापस child;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mtk_rpmsg_रेजिस्टर_device(काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev,
				     काष्ठा rpmsg_channel_info *info)
अणु
	काष्ठा rpmsg_device *rpdev;
	काष्ठा mtk_rpmsg_device *mdev;
	काष्ठा platक्रमm_device *pdev = mtk_subdev->pdev;

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	mdev->mtk_subdev = mtk_subdev;

	rpdev = &mdev->rpdev;
	rpdev->ops = &mtk_rpmsg_device_ops;
	rpdev->src = info->src;
	rpdev->dst = info->dst;
	strscpy(rpdev->id.name, info->name, RPMSG_NAME_SIZE);

	rpdev->dev.of_node =
		mtk_rpmsg_match_device_subnode(pdev->dev.of_node, info->name);
	rpdev->dev.parent = &pdev->dev;
	rpdev->dev.release = mtk_rpmsg_release_device;

	वापस rpmsg_रेजिस्टर_device(rpdev);
पूर्ण

अटल व्योम mtk_रेजिस्टर_device_work_function(काष्ठा work_काष्ठा *रेजिस्टर_work)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *subdev = container_of(
		रेजिस्टर_work, काष्ठा mtk_rpmsg_rproc_subdev, रेजिस्टर_work);
	काष्ठा platक्रमm_device *pdev = subdev->pdev;
	काष्ठा mtk_rpmsg_channel_info *info;
	पूर्णांक ret;

	mutex_lock(&subdev->channels_lock);
	list_क्रम_each_entry(info, &subdev->channels, list) अणु
		अगर (info->रेजिस्टरed)
			जारी;

		ret = mtk_rpmsg_रेजिस्टर_device(subdev, &info->info);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Can't create rpmsg_device\n");
			जारी;
		पूर्ण

		info->रेजिस्टरed = true;
	पूर्ण
	mutex_unlock(&subdev->channels_lock);
पूर्ण

अटल पूर्णांक mtk_rpmsg_create_device(काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev,
				   अक्षर *name, u32 addr)
अणु
	काष्ठा mtk_rpmsg_channel_info *info;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	strscpy(info->info.name, name, RPMSG_NAME_SIZE);
	info->info.src = addr;
	info->info.dst = RPMSG_ADDR_ANY;
	mutex_lock(&mtk_subdev->channels_lock);
	list_add(&info->list, &mtk_subdev->channels);
	mutex_unlock(&mtk_subdev->channels_lock);

	schedule_work(&mtk_subdev->रेजिस्टर_work);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_rpmsg_ns_cb(काष्ठा rpmsg_device *rpdev, व्योम *data, पूर्णांक len,
			   व्योम *priv, u32 src)
अणु
	काष्ठा rpmsg_ns_msg *msg = data;
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev = priv;
	काष्ठा device *dev = &mtk_subdev->pdev->dev;

	पूर्णांक ret;

	अगर (len != माप(*msg)) अणु
		dev_err(dev, "malformed ns msg (%d)\n", len);
		वापस -EINVAL;
	पूर्ण

	/*
	 * the name service ept करोes _not_ beदीर्घ to a real rpmsg channel,
	 * and is handled by the rpmsg bus itself.
	 * क्रम sanity reasons, make sure a valid rpdev has _not_ sneaked
	 * in somehow.
	 */
	अगर (rpdev) अणु
		dev_err(dev, "anomaly: ns ept has an rpdev handle\n");
		वापस -EINVAL;
	पूर्ण

	/* करोn't trust the remote processor क्रम null terminating the name */
	msg->name[RPMSG_NAME_SIZE - 1] = '\0';

	dev_info(dev, "creating channel %s addr 0x%x\n", msg->name, msg->addr);

	ret = mtk_rpmsg_create_device(mtk_subdev, msg->name, msg->addr);
	अगर (ret) अणु
		dev_err(dev, "create rpmsg device failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_rpmsg_prepare(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev = to_mtk_subdev(subdev);

	/* a dedicated endpoपूर्णांक handles the name service msgs */
	अगर (mtk_subdev->info->ns_ipi_id >= 0) अणु
		mtk_subdev->ns_ept =
			__mtk_create_ept(mtk_subdev, शून्य, mtk_rpmsg_ns_cb,
					 mtk_subdev,
					 mtk_subdev->info->ns_ipi_id);
		अगर (!mtk_subdev->ns_ept) अणु
			dev_err(&mtk_subdev->pdev->dev,
				"failed to create name service endpoint\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_rpmsg_unprepare(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev = to_mtk_subdev(subdev);

	अगर (mtk_subdev->ns_ept) अणु
		mtk_rpmsg_destroy_ept(mtk_subdev->ns_ept);
		mtk_subdev->ns_ept = शून्य;
	पूर्ण
पूर्ण

अटल व्योम mtk_rpmsg_stop(काष्ठा rproc_subdev *subdev, bool crashed)
अणु
	काष्ठा mtk_rpmsg_channel_info *info, *next;
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev = to_mtk_subdev(subdev);
	काष्ठा device *dev = &mtk_subdev->pdev->dev;

	/*
	 * Destroy the name service endpoपूर्णांक here, to aव्योम new channel being
	 * created after the rpmsg_unरेजिस्टर_device loop below.
	 */
	अगर (mtk_subdev->ns_ept) अणु
		mtk_rpmsg_destroy_ept(mtk_subdev->ns_ept);
		mtk_subdev->ns_ept = शून्य;
	पूर्ण

	cancel_work_sync(&mtk_subdev->रेजिस्टर_work);

	mutex_lock(&mtk_subdev->channels_lock);
	list_क्रम_each_entry(info, &mtk_subdev->channels, list) अणु
		अगर (!info->रेजिस्टरed)
			जारी;
		अगर (rpmsg_unरेजिस्टर_device(dev, &info->info)) अणु
			dev_warn(
				dev,
				"rpmsg_unregister_device failed for %s.%d.%d\n",
				info->info.name, info->info.src,
				info->info.dst);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(info, next,
				 &mtk_subdev->channels, list) अणु
		list_del(&info->list);
		kमुक्त(info);
	पूर्ण
	mutex_unlock(&mtk_subdev->channels_lock);
पूर्ण

काष्ठा rproc_subdev *
mtk_rpmsg_create_rproc_subdev(काष्ठा platक्रमm_device *pdev,
			      काष्ठा mtk_rpmsg_info *info)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev;

	mtk_subdev = kzalloc(माप(*mtk_subdev), GFP_KERNEL);
	अगर (!mtk_subdev)
		वापस शून्य;

	mtk_subdev->pdev = pdev;
	mtk_subdev->subdev.prepare = mtk_rpmsg_prepare;
	mtk_subdev->subdev.stop = mtk_rpmsg_stop;
	mtk_subdev->subdev.unprepare = mtk_rpmsg_unprepare;
	mtk_subdev->info = info;
	INIT_LIST_HEAD(&mtk_subdev->channels);
	INIT_WORK(&mtk_subdev->रेजिस्टर_work,
		  mtk_रेजिस्टर_device_work_function);
	mutex_init(&mtk_subdev->channels_lock);

	वापस &mtk_subdev->subdev;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_rpmsg_create_rproc_subdev);

व्योम mtk_rpmsg_destroy_rproc_subdev(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा mtk_rpmsg_rproc_subdev *mtk_subdev = to_mtk_subdev(subdev);

	kमुक्त(mtk_subdev);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_rpmsg_destroy_rproc_subdev);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek scp rpmsg driver");
