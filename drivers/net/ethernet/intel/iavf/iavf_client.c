<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश "iavf.h"
#समावेश "iavf_prototype.h"
#समावेश "iavf_client.h"

अटल
स्थिर अक्षर iavf_client_पूर्णांकerface_version_str[] = IAVF_CLIENT_VERSION_STR;
अटल काष्ठा iavf_client *vf_रेजिस्टरed_client;
अटल LIST_HEAD(iavf_devices);
अटल DEFINE_MUTEX(iavf_device_mutex);

अटल u32 iavf_client_virtchnl_send(काष्ठा iavf_info *ldev,
				     काष्ठा iavf_client *client,
				     u8 *msg, u16 len);

अटल पूर्णांक iavf_client_setup_qvlist(काष्ठा iavf_info *ldev,
				    काष्ठा iavf_client *client,
				    काष्ठा iavf_qvlist_info *qvlist_info);

अटल काष्ठा iavf_ops iavf_lan_ops = अणु
	.virtchnl_send = iavf_client_virtchnl_send,
	.setup_qvlist = iavf_client_setup_qvlist,
पूर्ण;

/**
 * iavf_client_get_params - retrieve relevant client parameters
 * @vsi: VSI with parameters
 * @params: client param काष्ठा
 **/
अटल
व्योम iavf_client_get_params(काष्ठा iavf_vsi *vsi, काष्ठा iavf_params *params)
अणु
	पूर्णांक i;

	स_रखो(params, 0, माप(काष्ठा iavf_params));
	params->mtu = vsi->netdev->mtu;
	params->link_up = vsi->back->link_up;

	क्रम (i = 0; i < IAVF_MAX_USER_PRIORITY; i++) अणु
		params->qos.prio_qos[i].tc = 0;
		params->qos.prio_qos[i].qs_handle = vsi->qs_handle;
	पूर्ण
पूर्ण

/**
 * iavf_notअगरy_client_message - call the client message receive callback
 * @vsi: the VSI associated with this client
 * @msg: message buffer
 * @len: length of message
 *
 * If there is a client to this VSI, call the client
 **/
व्योम iavf_notअगरy_client_message(काष्ठा iavf_vsi *vsi, u8 *msg, u16 len)
अणु
	काष्ठा iavf_client_instance *cinst;

	अगर (!vsi)
		वापस;

	cinst = vsi->back->cinst;
	अगर (!cinst || !cinst->client || !cinst->client->ops ||
	    !cinst->client->ops->virtchnl_receive) अणु
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance virtchnl_receive function\n");
		वापस;
	पूर्ण
	cinst->client->ops->virtchnl_receive(&cinst->lan_info,  cinst->client,
					     msg, len);
पूर्ण

/**
 * iavf_notअगरy_client_l2_params - call the client notअगरy callback
 * @vsi: the VSI with l2 param changes
 *
 * If there is a client to this VSI, call the client
 **/
व्योम iavf_notअगरy_client_l2_params(काष्ठा iavf_vsi *vsi)
अणु
	काष्ठा iavf_client_instance *cinst;
	काष्ठा iavf_params params;

	अगर (!vsi)
		वापस;

	cinst = vsi->back->cinst;

	अगर (!cinst || !cinst->client || !cinst->client->ops ||
	    !cinst->client->ops->l2_param_change) अणु
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance l2_param_change function\n");
		वापस;
	पूर्ण
	iavf_client_get_params(vsi, &params);
	cinst->lan_info.params = params;
	cinst->client->ops->l2_param_change(&cinst->lan_info, cinst->client,
					    &params);
पूर्ण

/**
 * iavf_notअगरy_client_खोलो - call the client खोलो callback
 * @vsi: the VSI with netdev खोलोed
 *
 * If there is a client to this netdev, call the client with खोलो
 **/
व्योम iavf_notअगरy_client_खोलो(काष्ठा iavf_vsi *vsi)
अणु
	काष्ठा iavf_adapter *adapter = vsi->back;
	काष्ठा iavf_client_instance *cinst = adapter->cinst;
	पूर्णांक ret;

	अगर (!cinst || !cinst->client || !cinst->client->ops ||
	    !cinst->client->ops->खोलो) अणु
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance open function\n");
		वापस;
	पूर्ण
	अगर (!(test_bit(__IAVF_CLIENT_INSTANCE_OPENED, &cinst->state))) अणु
		ret = cinst->client->ops->खोलो(&cinst->lan_info, cinst->client);
		अगर (!ret)
			set_bit(__IAVF_CLIENT_INSTANCE_OPENED, &cinst->state);
	पूर्ण
पूर्ण

/**
 * iavf_client_release_qvlist - send a message to the PF to release iwarp qv map
 * @ldev: poपूर्णांकer to L2 context.
 *
 * Return 0 on success or < 0 on error
 **/
अटल पूर्णांक iavf_client_release_qvlist(काष्ठा iavf_info *ldev)
अणु
	काष्ठा iavf_adapter *adapter = ldev->vf;
	क्रमागत iavf_status err;

	अगर (adapter->aq_required)
		वापस -EAGAIN;

	err = iavf_aq_send_msg_to_pf(&adapter->hw,
				     VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP,
				     IAVF_SUCCESS, शून्य, 0, शून्य);

	अगर (err)
		dev_err(&adapter->pdev->dev,
			"Unable to send iWarp vector release message to PF, error %d, aq status %d\n",
			err, adapter->hw.aq.asq_last_status);

	वापस err;
पूर्ण

/**
 * iavf_notअगरy_client_बंद - call the client बंद callback
 * @vsi: the VSI with netdev बंदd
 * @reset: true when बंद called due to reset pending
 *
 * If there is a client to this netdev, call the client with बंद
 **/
व्योम iavf_notअगरy_client_बंद(काष्ठा iavf_vsi *vsi, bool reset)
अणु
	काष्ठा iavf_adapter *adapter = vsi->back;
	काष्ठा iavf_client_instance *cinst = adapter->cinst;

	अगर (!cinst || !cinst->client || !cinst->client->ops ||
	    !cinst->client->ops->बंद) अणु
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance close function\n");
		वापस;
	पूर्ण
	cinst->client->ops->बंद(&cinst->lan_info, cinst->client, reset);
	iavf_client_release_qvlist(&cinst->lan_info);
	clear_bit(__IAVF_CLIENT_INSTANCE_OPENED, &cinst->state);
पूर्ण

/**
 * iavf_client_add_instance - add a client instance to the instance list
 * @adapter: poपूर्णांकer to the board काष्ठा
 *
 * Returns cinst ptr on success, शून्य on failure
 **/
अटल काष्ठा iavf_client_instance *
iavf_client_add_instance(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_client_instance *cinst = शून्य;
	काष्ठा iavf_vsi *vsi = &adapter->vsi;
	काष्ठा netdev_hw_addr *mac = शून्य;
	काष्ठा iavf_params params;

	अगर (!vf_रेजिस्टरed_client)
		जाओ out;

	अगर (adapter->cinst) अणु
		cinst = adapter->cinst;
		जाओ out;
	पूर्ण

	cinst = kzalloc(माप(*cinst), GFP_KERNEL);
	अगर (!cinst)
		जाओ out;

	cinst->lan_info.vf = (व्योम *)adapter;
	cinst->lan_info.netdev = vsi->netdev;
	cinst->lan_info.pcidev = adapter->pdev;
	cinst->lan_info.fid = 0;
	cinst->lan_info.ftype = IAVF_CLIENT_FTYPE_VF;
	cinst->lan_info.hw_addr = adapter->hw.hw_addr;
	cinst->lan_info.ops = &iavf_lan_ops;
	cinst->lan_info.version.major = IAVF_CLIENT_VERSION_MAJOR;
	cinst->lan_info.version.minor = IAVF_CLIENT_VERSION_MINOR;
	cinst->lan_info.version.build = IAVF_CLIENT_VERSION_BUILD;
	iavf_client_get_params(vsi, &params);
	cinst->lan_info.params = params;
	set_bit(__IAVF_CLIENT_INSTANCE_NONE, &cinst->state);

	cinst->lan_info.msix_count = adapter->num_iwarp_msix;
	cinst->lan_info.msix_entries =
			&adapter->msix_entries[adapter->iwarp_base_vector];

	mac = list_first_entry(&cinst->lan_info.netdev->dev_addrs.list,
			       काष्ठा netdev_hw_addr, list);
	अगर (mac)
		ether_addr_copy(cinst->lan_info.lanmac, mac->addr);
	अन्यथा
		dev_err(&adapter->pdev->dev, "MAC address list is empty!\n");

	cinst->client = vf_रेजिस्टरed_client;
	adapter->cinst = cinst;
out:
	वापस cinst;
पूर्ण

/**
 * iavf_client_del_instance - हटाओs a client instance from the list
 * @adapter: poपूर्णांकer to the board काष्ठा
 *
 **/
अटल
व्योम iavf_client_del_instance(काष्ठा iavf_adapter *adapter)
अणु
	kमुक्त(adapter->cinst);
	adapter->cinst = शून्य;
पूर्ण

/**
 * iavf_client_subtask - client मुख्यtenance work
 * @adapter: board निजी काष्ठाure
 **/
व्योम iavf_client_subtask(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_client *client = vf_रेजिस्टरed_client;
	काष्ठा iavf_client_instance *cinst;
	पूर्णांक ret = 0;

	अगर (adapter->state < __IAVF_DOWN)
		वापस;

	/* first check client is रेजिस्टरed */
	अगर (!client)
		वापस;

	/* Add the client instance to the instance list */
	cinst = iavf_client_add_instance(adapter);
	अगर (!cinst)
		वापस;

	dev_info(&adapter->pdev->dev, "Added instance of Client %s\n",
		 client->name);

	अगर (!test_bit(__IAVF_CLIENT_INSTANCE_OPENED, &cinst->state)) अणु
		/* Send an Open request to the client */

		अगर (client->ops && client->ops->खोलो)
			ret = client->ops->खोलो(&cinst->lan_info, client);
		अगर (!ret)
			set_bit(__IAVF_CLIENT_INSTANCE_OPENED,
				&cinst->state);
		अन्यथा
			/* हटाओ client instance */
			iavf_client_del_instance(adapter);
	पूर्ण
पूर्ण

/**
 * iavf_lan_add_device - add a lan device काष्ठा to the list of lan devices
 * @adapter: poपूर्णांकer to the board काष्ठा
 *
 * Returns 0 on success or none 0 on error
 **/
पूर्णांक iavf_lan_add_device(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_device *ldev;
	पूर्णांक ret = 0;

	mutex_lock(&iavf_device_mutex);
	list_क्रम_each_entry(ldev, &iavf_devices, list) अणु
		अगर (ldev->vf == adapter) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण
	ldev = kzalloc(माप(*ldev), GFP_KERNEL);
	अगर (!ldev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ldev->vf = adapter;
	INIT_LIST_HEAD(&ldev->list);
	list_add(&ldev->list, &iavf_devices);
	dev_info(&adapter->pdev->dev, "Added LAN device bus=0x%02x dev=0x%02x func=0x%02x\n",
		 adapter->hw.bus.bus_id, adapter->hw.bus.device,
		 adapter->hw.bus.func);

	/* Since in some हालs रेजिस्टर may have happened beक्रमe a device माला_लो
	 * added, we can schedule a subtask to go initiate the clients.
	 */
	adapter->flags |= IAVF_FLAG_SERVICE_CLIENT_REQUESTED;

out:
	mutex_unlock(&iavf_device_mutex);
	वापस ret;
पूर्ण

/**
 * iavf_lan_del_device - हटाओs a lan device from the device list
 * @adapter: poपूर्णांकer to the board काष्ठा
 *
 * Returns 0 on success or non-0 on error
 **/
पूर्णांक iavf_lan_del_device(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_device *ldev, *पंचांगp;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&iavf_device_mutex);
	list_क्रम_each_entry_safe(ldev, पंचांगp, &iavf_devices, list) अणु
		अगर (ldev->vf == adapter) अणु
			dev_info(&adapter->pdev->dev,
				 "Deleted LAN device bus=0x%02x dev=0x%02x func=0x%02x\n",
				 adapter->hw.bus.bus_id, adapter->hw.bus.device,
				 adapter->hw.bus.func);
			list_del(&ldev->list);
			kमुक्त(ldev);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&iavf_device_mutex);
	वापस ret;
पूर्ण

/**
 * iavf_client_release - release client specअगरic resources
 * @client: poपूर्णांकer to the रेजिस्टरed client
 *
 **/
अटल व्योम iavf_client_release(काष्ठा iavf_client *client)
अणु
	काष्ठा iavf_client_instance *cinst;
	काष्ठा iavf_device *ldev;
	काष्ठा iavf_adapter *adapter;

	mutex_lock(&iavf_device_mutex);
	list_क्रम_each_entry(ldev, &iavf_devices, list) अणु
		adapter = ldev->vf;
		cinst = adapter->cinst;
		अगर (!cinst)
			जारी;
		अगर (test_bit(__IAVF_CLIENT_INSTANCE_OPENED, &cinst->state)) अणु
			अगर (client->ops && client->ops->बंद)
				client->ops->बंद(&cinst->lan_info, client,
						   false);
			iavf_client_release_qvlist(&cinst->lan_info);
			clear_bit(__IAVF_CLIENT_INSTANCE_OPENED, &cinst->state);

			dev_warn(&adapter->pdev->dev,
				 "Client %s instance closed\n", client->name);
		पूर्ण
		/* delete the client instance */
		iavf_client_del_instance(adapter);
		dev_info(&adapter->pdev->dev, "Deleted client instance of Client %s\n",
			 client->name);
	पूर्ण
	mutex_unlock(&iavf_device_mutex);
पूर्ण

/**
 * iavf_client_prepare - prepare client specअगरic resources
 * @client: poपूर्णांकer to the रेजिस्टरed client
 *
 **/
अटल व्योम iavf_client_prepare(काष्ठा iavf_client *client)
अणु
	काष्ठा iavf_device *ldev;
	काष्ठा iavf_adapter *adapter;

	mutex_lock(&iavf_device_mutex);
	list_क्रम_each_entry(ldev, &iavf_devices, list) अणु
		adapter = ldev->vf;
		/* Signal the watchकरोg to service the client */
		adapter->flags |= IAVF_FLAG_SERVICE_CLIENT_REQUESTED;
	पूर्ण
	mutex_unlock(&iavf_device_mutex);
पूर्ण

/**
 * iavf_client_virtchnl_send - send a message to the PF instance
 * @ldev: poपूर्णांकer to L2 context.
 * @client: Client poपूर्णांकer.
 * @msg: poपूर्णांकer to message buffer
 * @len: message length
 *
 * Return 0 on success or < 0 on error
 **/
अटल u32 iavf_client_virtchnl_send(काष्ठा iavf_info *ldev,
				     काष्ठा iavf_client *client,
				     u8 *msg, u16 len)
अणु
	काष्ठा iavf_adapter *adapter = ldev->vf;
	क्रमागत iavf_status err;

	अगर (adapter->aq_required)
		वापस -EAGAIN;

	err = iavf_aq_send_msg_to_pf(&adapter->hw, VIRTCHNL_OP_IWARP,
				     IAVF_SUCCESS, msg, len, शून्य);
	अगर (err)
		dev_err(&adapter->pdev->dev, "Unable to send iWarp message to PF, error %d, aq status %d\n",
			err, adapter->hw.aq.asq_last_status);

	वापस err;
पूर्ण

/**
 * iavf_client_setup_qvlist - send a message to the PF to setup iwarp qv map
 * @ldev: poपूर्णांकer to L2 context.
 * @client: Client poपूर्णांकer.
 * @qvlist_info: queue and vector list
 *
 * Return 0 on success or < 0 on error
 **/
अटल पूर्णांक iavf_client_setup_qvlist(काष्ठा iavf_info *ldev,
				    काष्ठा iavf_client *client,
				    काष्ठा iavf_qvlist_info *qvlist_info)
अणु
	काष्ठा virtchnl_iwarp_qvlist_info *v_qvlist_info;
	काष्ठा iavf_adapter *adapter = ldev->vf;
	काष्ठा iavf_qv_info *qv_info;
	क्रमागत iavf_status err;
	u32 v_idx, i;
	माप_प्रकार msg_size;

	अगर (adapter->aq_required)
		वापस -EAGAIN;

	/* A quick check on whether the vectors beदीर्घ to the client */
	क्रम (i = 0; i < qvlist_info->num_vectors; i++) अणु
		qv_info = &qvlist_info->qv_info[i];
		अगर (!qv_info)
			जारी;
		v_idx = qv_info->v_idx;
		अगर ((v_idx >=
		    (adapter->iwarp_base_vector + adapter->num_iwarp_msix)) ||
		    (v_idx < adapter->iwarp_base_vector))
			वापस -EINVAL;
	पूर्ण

	v_qvlist_info = (काष्ठा virtchnl_iwarp_qvlist_info *)qvlist_info;
	msg_size = काष्ठा_size(v_qvlist_info, qv_info,
			       v_qvlist_info->num_vectors - 1);

	adapter->client_pending |= BIT(VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP);
	err = iavf_aq_send_msg_to_pf(&adapter->hw,
				VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP, IAVF_SUCCESS,
				(u8 *)v_qvlist_info, msg_size, शून्य);

	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Unable to send iWarp vector config message to PF, error %d, aq status %d\n",
			err, adapter->hw.aq.asq_last_status);
		जाओ out;
	पूर्ण

	err = -EBUSY;
	क्रम (i = 0; i < 5; i++) अणु
		msleep(100);
		अगर (!(adapter->client_pending &
		      BIT(VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP))) अणु
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

/**
 * iavf_रेजिस्टर_client - Register a iavf client driver with the L2 driver
 * @client: poपूर्णांकer to the iavf_client काष्ठा
 *
 * Returns 0 on success or non-0 on error
 **/
पूर्णांक iavf_रेजिस्टर_client(काष्ठा iavf_client *client)
अणु
	पूर्णांक ret = 0;

	अगर (!client) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (म_माप(client->name) == 0) अणु
		pr_info("iavf: Failed to register client with no name\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (vf_रेजिस्टरed_client) अणु
		pr_info("iavf: Client %s has already been registered!\n",
			client->name);
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	अगर ((client->version.major != IAVF_CLIENT_VERSION_MAJOR) ||
	    (client->version.minor != IAVF_CLIENT_VERSION_MINOR)) अणु
		pr_info("iavf: Failed to register client %s due to mismatched client interface version\n",
			client->name);
		pr_info("Client is using version: %02d.%02d.%02d while LAN driver supports %s\n",
			client->version.major, client->version.minor,
			client->version.build,
			iavf_client_पूर्णांकerface_version_str);
		ret = -EIO;
		जाओ out;
	पूर्ण

	vf_रेजिस्टरed_client = client;

	iavf_client_prepare(client);

	pr_info("iavf: Registered client %s with return code %d\n",
		client->name, ret);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(iavf_रेजिस्टर_client);

/**
 * iavf_unरेजिस्टर_client - Unरेजिस्टर a iavf client driver with the L2 driver
 * @client: poपूर्णांकer to the iavf_client काष्ठा
 *
 * Returns 0 on success or non-0 on error
 **/
पूर्णांक iavf_unरेजिस्टर_client(काष्ठा iavf_client *client)
अणु
	पूर्णांक ret = 0;

	/* When a unरेजिस्टर request comes through we would have to send
	 * a बंद क्रम each of the client instances that were खोलोed.
	 * client_release function is called to handle this.
	 */
	iavf_client_release(client);

	अगर (vf_रेजिस्टरed_client != client) अणु
		pr_info("iavf: Client %s has not been registered\n",
			client->name);
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	vf_रेजिस्टरed_client = शून्य;
	pr_info("iavf: Unregistered client %s\n", client->name);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(iavf_unरेजिस्टर_client);
