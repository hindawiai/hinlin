<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of_device.h>
#समावेश <linux/soc/qcom/apr.h>
#समावेश <linux/soc/qcom/pdr.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/of.h>

काष्ठा apr अणु
	काष्ठा rpmsg_endpoपूर्णांक *ch;
	काष्ठा device *dev;
	spinlock_t svcs_lock;
	spinlock_t rx_lock;
	काष्ठा idr svcs_idr;
	पूर्णांक dest_करोमुख्य_id;
	काष्ठा pdr_handle *pdr;
	काष्ठा workqueue_काष्ठा *rxwq;
	काष्ठा work_काष्ठा rx_work;
	काष्ठा list_head rx_list;
पूर्ण;

काष्ठा apr_rx_buf अणु
	काष्ठा list_head node;
	पूर्णांक len;
	uपूर्णांक8_t buf[];
पूर्ण;

/**
 * apr_send_pkt() - Send a apr message from apr device
 *
 * @adev: Poपूर्णांकer to previously रेजिस्टरed apr device.
 * @pkt: Poपूर्णांकer to apr packet to send
 *
 * Return: Will be an negative on packet size on success.
 */
पूर्णांक apr_send_pkt(काष्ठा apr_device *adev, काष्ठा apr_pkt *pkt)
अणु
	काष्ठा apr *apr = dev_get_drvdata(adev->dev.parent);
	काष्ठा apr_hdr *hdr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&adev->lock, flags);

	hdr = &pkt->hdr;
	hdr->src_करोमुख्य = APR_DOMAIN_APPS;
	hdr->src_svc = adev->svc_id;
	hdr->dest_करोमुख्य = adev->करोमुख्य_id;
	hdr->dest_svc = adev->svc_id;

	ret = rpmsg_trysend(apr->ch, pkt, hdr->pkt_size);
	spin_unlock_irqrestore(&adev->lock, flags);

	वापस ret ? ret : hdr->pkt_size;
पूर्ण
EXPORT_SYMBOL_GPL(apr_send_pkt);

अटल व्योम apr_dev_release(काष्ठा device *dev)
अणु
	काष्ठा apr_device *adev = to_apr_device(dev);

	kमुक्त(adev);
पूर्ण

अटल पूर्णांक apr_callback(काष्ठा rpmsg_device *rpdev, व्योम *buf,
				  पूर्णांक len, व्योम *priv, u32 addr)
अणु
	काष्ठा apr *apr = dev_get_drvdata(&rpdev->dev);
	काष्ठा apr_rx_buf *abuf;
	अचिन्हित दीर्घ flags;

	अगर (len <= APR_HDR_SIZE) अणु
		dev_err(apr->dev, "APR: Improper apr pkt received:%p %d\n",
			buf, len);
		वापस -EINVAL;
	पूर्ण

	abuf = kzalloc(माप(*abuf) + len, GFP_ATOMIC);
	अगर (!abuf)
		वापस -ENOMEM;

	abuf->len = len;
	स_नकल(abuf->buf, buf, len);

	spin_lock_irqsave(&apr->rx_lock, flags);
	list_add_tail(&abuf->node, &apr->rx_list);
	spin_unlock_irqrestore(&apr->rx_lock, flags);

	queue_work(apr->rxwq, &apr->rx_work);

	वापस 0;
पूर्ण


अटल पूर्णांक apr_करो_rx_callback(काष्ठा apr *apr, काष्ठा apr_rx_buf *abuf)
अणु
	uपूर्णांक16_t hdr_size, msg_type, ver, svc_id;
	काष्ठा apr_device *svc = शून्य;
	काष्ठा apr_driver *adrv = शून्य;
	काष्ठा apr_resp_pkt resp;
	काष्ठा apr_hdr *hdr;
	अचिन्हित दीर्घ flags;
	व्योम *buf = abuf->buf;
	पूर्णांक len = abuf->len;

	hdr = buf;
	ver = APR_HDR_FIELD_VER(hdr->hdr_field);
	अगर (ver > APR_PKT_VER + 1)
		वापस -EINVAL;

	hdr_size = APR_HDR_FIELD_SIZE_BYTES(hdr->hdr_field);
	अगर (hdr_size < APR_HDR_SIZE) अणु
		dev_err(apr->dev, "APR: Wrong hdr size:%d\n", hdr_size);
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->pkt_size < APR_HDR_SIZE || hdr->pkt_size != len) अणु
		dev_err(apr->dev, "APR: Wrong packet size\n");
		वापस -EINVAL;
	पूर्ण

	msg_type = APR_HDR_FIELD_MT(hdr->hdr_field);
	अगर (msg_type >= APR_MSG_TYPE_MAX) अणु
		dev_err(apr->dev, "APR: Wrong message type: %d\n", msg_type);
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->src_करोमुख्य >= APR_DOMAIN_MAX ||
			hdr->dest_करोमुख्य >= APR_DOMAIN_MAX ||
			hdr->src_svc >= APR_SVC_MAX ||
			hdr->dest_svc >= APR_SVC_MAX) अणु
		dev_err(apr->dev, "APR: Wrong APR header\n");
		वापस -EINVAL;
	पूर्ण

	svc_id = hdr->dest_svc;
	spin_lock_irqsave(&apr->svcs_lock, flags);
	svc = idr_find(&apr->svcs_idr, svc_id);
	अगर (svc && svc->dev.driver)
		adrv = to_apr_driver(svc->dev.driver);
	spin_unlock_irqrestore(&apr->svcs_lock, flags);

	अगर (!adrv) अणु
		dev_err(apr->dev, "APR: service is not registered\n");
		वापस -EINVAL;
	पूर्ण

	resp.hdr = *hdr;
	resp.payload_size = hdr->pkt_size - hdr_size;

	/*
	 * NOTE: hdr_size is not same as APR_HDR_SIZE as remote can include
	 * optional headers in to apr_hdr which should be ignored
	 */
	अगर (resp.payload_size > 0)
		resp.payload = buf + hdr_size;

	adrv->callback(svc, &resp);

	वापस 0;
पूर्ण

अटल व्योम apr_rxwq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा apr *apr = container_of(work, काष्ठा apr, rx_work);
	काष्ठा apr_rx_buf *abuf, *b;
	अचिन्हित दीर्घ flags;

	अगर (!list_empty(&apr->rx_list)) अणु
		list_क्रम_each_entry_safe(abuf, b, &apr->rx_list, node) अणु
			apr_करो_rx_callback(apr, abuf);
			spin_lock_irqsave(&apr->rx_lock, flags);
			list_del(&abuf->node);
			spin_unlock_irqrestore(&apr->rx_lock, flags);
			kमुक्त(abuf);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक apr_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा apr_device *adev = to_apr_device(dev);
	काष्ठा apr_driver *adrv = to_apr_driver(drv);
	स्थिर काष्ठा apr_device_id *id = adrv->id_table;

	/* Attempt an OF style match first */
	अगर (of_driver_match_device(dev, drv))
		वापस 1;

	अगर (!id)
		वापस 0;

	जबतक (id->करोमुख्य_id != 0 || id->svc_id != 0) अणु
		अगर (id->करोमुख्य_id == adev->करोमुख्य_id &&
		    id->svc_id == adev->svc_id)
			वापस 1;
		id++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apr_device_probe(काष्ठा device *dev)
अणु
	काष्ठा apr_device *adev = to_apr_device(dev);
	काष्ठा apr_driver *adrv = to_apr_driver(dev->driver);

	वापस adrv->probe(adev);
पूर्ण

अटल पूर्णांक apr_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा apr_device *adev = to_apr_device(dev);
	काष्ठा apr_driver *adrv;
	काष्ठा apr *apr = dev_get_drvdata(adev->dev.parent);

	अगर (dev->driver) अणु
		adrv = to_apr_driver(dev->driver);
		अगर (adrv->हटाओ)
			adrv->हटाओ(adev);
		spin_lock(&apr->svcs_lock);
		idr_हटाओ(&apr->svcs_idr, adev->svc_id);
		spin_unlock(&apr->svcs_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apr_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा apr_device *adev = to_apr_device(dev);
	पूर्णांक ret;

	ret = of_device_uevent_modalias(dev, env);
	अगर (ret != -ENODEV)
		वापस ret;

	वापस add_uevent_var(env, "MODALIAS=apr:%s", adev->name);
पूर्ण

काष्ठा bus_type aprbus = अणु
	.name		= "aprbus",
	.match		= apr_device_match,
	.probe		= apr_device_probe,
	.uevent		= apr_uevent,
	.हटाओ		= apr_device_हटाओ,
पूर्ण;
EXPORT_SYMBOL_GPL(aprbus);

अटल पूर्णांक apr_add_device(काष्ठा device *dev, काष्ठा device_node *np,
			  स्थिर काष्ठा apr_device_id *id)
अणु
	काष्ठा apr *apr = dev_get_drvdata(dev);
	काष्ठा apr_device *adev = शून्य;
	पूर्णांक ret;

	adev = kzalloc(माप(*adev), GFP_KERNEL);
	अगर (!adev)
		वापस -ENOMEM;

	spin_lock_init(&adev->lock);

	adev->svc_id = id->svc_id;
	adev->करोमुख्य_id = id->करोमुख्य_id;
	adev->version = id->svc_version;
	अगर (np)
		snम_लिखो(adev->name, APR_NAME_SIZE, "%pOFn", np);
	अन्यथा
		strscpy(adev->name, id->name, APR_NAME_SIZE);

	dev_set_name(&adev->dev, "aprsvc:%s:%x:%x", adev->name,
		     id->करोमुख्य_id, id->svc_id);

	adev->dev.bus = &aprbus;
	adev->dev.parent = dev;
	adev->dev.of_node = np;
	adev->dev.release = apr_dev_release;
	adev->dev.driver = शून्य;

	spin_lock(&apr->svcs_lock);
	idr_alloc(&apr->svcs_idr, adev, id->svc_id,
		  id->svc_id + 1, GFP_ATOMIC);
	spin_unlock(&apr->svcs_lock);

	of_property_पढ़ो_string_index(np, "qcom,protection-domain",
				      1, &adev->service_path);

	dev_info(dev, "Adding APR dev: %s\n", dev_name(&adev->dev));

	ret = device_रेजिस्टर(&adev->dev);
	अगर (ret) अणु
		dev_err(dev, "device_register failed: %d\n", ret);
		put_device(&adev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक of_apr_add_pd_lookups(काष्ठा device *dev)
अणु
	स्थिर अक्षर *service_name, *service_path;
	काष्ठा apr *apr = dev_get_drvdata(dev);
	काष्ठा device_node *node;
	काष्ठा pdr_service *pds;
	पूर्णांक ret;

	क्रम_each_child_of_node(dev->of_node, node) अणु
		ret = of_property_पढ़ो_string_index(node, "qcom,protection-domain",
						    0, &service_name);
		अगर (ret < 0)
			जारी;

		ret = of_property_पढ़ो_string_index(node, "qcom,protection-domain",
						    1, &service_path);
		अगर (ret < 0) अणु
			dev_err(dev, "pdr service path missing: %d\n", ret);
			वापस ret;
		पूर्ण

		pds = pdr_add_lookup(apr->pdr, service_name, service_path);
		अगर (IS_ERR(pds) && PTR_ERR(pds) != -EALREADY) अणु
			dev_err(dev, "pdr add lookup failed: %ld\n", PTR_ERR(pds));
			वापस PTR_ERR(pds);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम of_रेजिस्टर_apr_devices(काष्ठा device *dev, स्थिर अक्षर *svc_path)
अणु
	काष्ठा apr *apr = dev_get_drvdata(dev);
	काष्ठा device_node *node;
	स्थिर अक्षर *service_path;
	पूर्णांक ret;

	क्रम_each_child_of_node(dev->of_node, node) अणु
		काष्ठा apr_device_id id = अणु अणु0पूर्ण पूर्ण;

		/*
		 * This function is called with svc_path शून्य during
		 * apr_probe(), in which हाल we रेजिस्टर any apr devices
		 * without a qcom,protection-करोमुख्य specअगरied.
		 *
		 * Then as the protection करोमुख्यs becomes available
		 * (अगर applicable) this function is again called, but with
		 * svc_path representing the service becoming available. In
		 * this हाल we रेजिस्टर any apr devices with a matching
		 * qcom,protection-करोमुख्य.
		 */

		ret = of_property_पढ़ो_string_index(node, "qcom,protection-domain",
						    1, &service_path);
		अगर (svc_path) अणु
			/* skip APR services that are PD independent */
			अगर (ret)
				जारी;

			/* skip APR services whose PD paths करोn't match */
			अगर (म_भेद(service_path, svc_path))
				जारी;
		पूर्ण अन्यथा अणु
			/* skip APR services whose PD lookups are रेजिस्टरed */
			अगर (ret == 0)
				जारी;
		पूर्ण

		अगर (of_property_पढ़ो_u32(node, "reg", &id.svc_id))
			जारी;

		id.करोमुख्य_id = apr->dest_करोमुख्य_id;

		अगर (apr_add_device(dev, node, &id))
			dev_err(dev, "Failed to add apr %d svc\n", id.svc_id);
	पूर्ण
पूर्ण

अटल पूर्णांक apr_हटाओ_device(काष्ठा device *dev, व्योम *svc_path)
अणु
	काष्ठा apr_device *adev = to_apr_device(dev);

	अगर (svc_path && adev->service_path) अणु
		अगर (!म_भेद(adev->service_path, (अक्षर *)svc_path))
			device_unरेजिस्टर(&adev->dev);
	पूर्ण अन्यथा अणु
		device_unरेजिस्टर(&adev->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम apr_pd_status(पूर्णांक state, अक्षर *svc_path, व्योम *priv)
अणु
	काष्ठा apr *apr = (काष्ठा apr *)priv;

	चयन (state) अणु
	हाल SERVREG_SERVICE_STATE_UP:
		of_रेजिस्टर_apr_devices(apr->dev, svc_path);
		अवरोध;
	हाल SERVREG_SERVICE_STATE_DOWN:
		device_क्रम_each_child(apr->dev, svc_path, apr_हटाओ_device);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक apr_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा device *dev = &rpdev->dev;
	काष्ठा apr *apr;
	पूर्णांक ret;

	apr = devm_kzalloc(dev, माप(*apr), GFP_KERNEL);
	अगर (!apr)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32(dev->of_node, "qcom,apr-domain", &apr->dest_करोमुख्य_id);
	अगर (ret) अणु
		dev_err(dev, "APR Domain ID not specified in DT\n");
		वापस ret;
	पूर्ण

	dev_set_drvdata(dev, apr);
	apr->ch = rpdev->ept;
	apr->dev = dev;
	apr->rxwq = create_singlethपढ़ो_workqueue("qcom_apr_rx");
	अगर (!apr->rxwq) अणु
		dev_err(apr->dev, "Failed to start Rx WQ\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_WORK(&apr->rx_work, apr_rxwq);

	apr->pdr = pdr_handle_alloc(apr_pd_status, apr);
	अगर (IS_ERR(apr->pdr)) अणु
		dev_err(dev, "Failed to init PDR handle\n");
		ret = PTR_ERR(apr->pdr);
		जाओ destroy_wq;
	पूर्ण

	INIT_LIST_HEAD(&apr->rx_list);
	spin_lock_init(&apr->rx_lock);
	spin_lock_init(&apr->svcs_lock);
	idr_init(&apr->svcs_idr);

	ret = of_apr_add_pd_lookups(dev);
	अगर (ret)
		जाओ handle_release;

	of_रेजिस्टर_apr_devices(dev, शून्य);

	वापस 0;

handle_release:
	pdr_handle_release(apr->pdr);
destroy_wq:
	destroy_workqueue(apr->rxwq);
	वापस ret;
पूर्ण

अटल व्योम apr_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा apr *apr = dev_get_drvdata(&rpdev->dev);

	pdr_handle_release(apr->pdr);
	device_क्रम_each_child(&rpdev->dev, शून्य, apr_हटाओ_device);
	flush_workqueue(apr->rxwq);
	destroy_workqueue(apr->rxwq);
पूर्ण

/*
 * __apr_driver_रेजिस्टर() - Client driver registration with aprbus
 *
 * @drv:Client driver to be associated with client-device.
 * @owner: owning module/driver
 *
 * This API will रेजिस्टर the client driver with the aprbus
 * It is called from the driver's module-init function.
 */
पूर्णांक __apr_driver_रेजिस्टर(काष्ठा apr_driver *drv, काष्ठा module *owner)
अणु
	drv->driver.bus = &aprbus;
	drv->driver.owner = owner;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__apr_driver_रेजिस्टर);

/*
 * apr_driver_unरेजिस्टर() - Unकरो effect of apr_driver_रेजिस्टर
 *
 * @drv: Client driver to be unरेजिस्टरed
 */
व्योम apr_driver_unरेजिस्टर(काष्ठा apr_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(apr_driver_unरेजिस्टर);

अटल स्थिर काष्ठा of_device_id apr_of_match[] = अणु
	अणु .compatible = "qcom,apr"पूर्ण,
	अणु .compatible = "qcom,apr-v2"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, apr_of_match);

अटल काष्ठा rpmsg_driver apr_driver = अणु
	.probe = apr_probe,
	.हटाओ = apr_हटाओ,
	.callback = apr_callback,
	.drv = अणु
		.name = "qcom,apr",
		.of_match_table = apr_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init apr_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&aprbus);
	अगर (!ret)
		ret = रेजिस्टर_rpmsg_driver(&apr_driver);
	अन्यथा
		bus_unरेजिस्टर(&aprbus);

	वापस ret;
पूर्ण

अटल व्योम __निकास apr_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&aprbus);
	unरेजिस्टर_rpmsg_driver(&apr_driver);
पूर्ण

subsys_initcall(apr_init);
module_निकास(apr_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm APR Bus");
