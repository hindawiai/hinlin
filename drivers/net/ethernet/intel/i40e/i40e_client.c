<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/net/पूर्णांकel/i40e_client.h>

#समावेश "i40e.h"
#समावेश "i40e_prototype.h"

अटल स्थिर अक्षर i40e_client_पूर्णांकerface_version_str[] = I40E_CLIENT_VERSION_STR;
अटल काष्ठा i40e_client *रेजिस्टरed_client;
अटल LIST_HEAD(i40e_devices);
अटल DEFINE_MUTEX(i40e_device_mutex);

अटल पूर्णांक i40e_client_virtchnl_send(काष्ठा i40e_info *ldev,
				     काष्ठा i40e_client *client,
				     u32 vf_id, u8 *msg, u16 len);

अटल पूर्णांक i40e_client_setup_qvlist(काष्ठा i40e_info *ldev,
				    काष्ठा i40e_client *client,
				    काष्ठा i40e_qvlist_info *qvlist_info);

अटल व्योम i40e_client_request_reset(काष्ठा i40e_info *ldev,
				      काष्ठा i40e_client *client,
				      u32 reset_level);

अटल पूर्णांक i40e_client_update_vsi_ctxt(काष्ठा i40e_info *ldev,
				       काष्ठा i40e_client *client,
				       bool is_vf, u32 vf_id,
				       u32 flag, u32 valid_flag);

अटल काष्ठा i40e_ops i40e_lan_ops = अणु
	.virtchnl_send = i40e_client_virtchnl_send,
	.setup_qvlist = i40e_client_setup_qvlist,
	.request_reset = i40e_client_request_reset,
	.update_vsi_ctxt = i40e_client_update_vsi_ctxt,
पूर्ण;

/**
 * i40e_client_get_params - Get the params that can change at runसमय
 * @vsi: the VSI with the message
 * @params: client param काष्ठा
 *
 **/
अटल
पूर्णांक i40e_client_get_params(काष्ठा i40e_vsi *vsi, काष्ठा i40e_params *params)
अणु
	काष्ठा i40e_dcbx_config *dcb_cfg = &vsi->back->hw.local_dcbx_config;
	पूर्णांक i = 0;

	क्रम (i = 0; i < I40E_MAX_USER_PRIORITY; i++) अणु
		u8 tc = dcb_cfg->etscfg.prioritytable[i];
		u16 qs_handle;

		/* If TC is not enabled क्रम VSI use TC0 क्रम UP */
		अगर (!(vsi->tc_config.enabled_tc & BIT(tc)))
			tc = 0;

		qs_handle = le16_to_cpu(vsi->info.qs_handle[tc]);
		params->qos.prio_qos[i].tc = tc;
		params->qos.prio_qos[i].qs_handle = qs_handle;
		अगर (qs_handle == I40E_AQ_VSI_QS_HANDLE_INVALID) अणु
			dev_err(&vsi->back->pdev->dev, "Invalid queue set handle for TC = %d, vsi id = %d\n",
				tc, vsi->id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	params->mtu = vsi->netdev->mtu;
	वापस 0;
पूर्ण

/**
 * i40e_notअगरy_client_of_vf_msg - call the client vf message callback
 * @vsi: the VSI with the message
 * @vf_id: the असलolute VF id that sent the message
 * @msg: message buffer
 * @len: length of the message
 *
 * If there is a client to this VSI, call the client
 **/
व्योम
i40e_notअगरy_client_of_vf_msg(काष्ठा i40e_vsi *vsi, u32 vf_id, u8 *msg, u16 len)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_client_instance *cdev = pf->cinst;

	अगर (!cdev || !cdev->client)
		वापस;
	अगर (!cdev->client->ops || !cdev->client->ops->virtchnl_receive) अणु
		dev_dbg(&pf->pdev->dev,
			"Cannot locate client instance virtual channel receive routine\n");
		वापस;
	पूर्ण
	अगर (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state)) अणु
		dev_dbg(&pf->pdev->dev, "Client is not open, abort virtchnl_receive\n");
		वापस;
	पूर्ण
	cdev->client->ops->virtchnl_receive(&cdev->lan_info, cdev->client,
					    vf_id, msg, len);
पूर्ण

/**
 * i40e_notअगरy_client_of_l2_param_changes - call the client notअगरy callback
 * @vsi: the VSI with l2 param changes
 *
 * If there is a client to this VSI, call the client
 **/
व्योम i40e_notअगरy_client_of_l2_param_changes(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_client_instance *cdev = pf->cinst;
	काष्ठा i40e_params params;

	अगर (!cdev || !cdev->client)
		वापस;
	अगर (!cdev->client->ops || !cdev->client->ops->l2_param_change) अणु
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance l2_param_change routine\n");
		वापस;
	पूर्ण
	अगर (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state)) अणु
		dev_dbg(&vsi->back->pdev->dev, "Client is not open, abort l2 param change\n");
		वापस;
	पूर्ण
	स_रखो(&params, 0, माप(params));
	i40e_client_get_params(vsi, &params);
	स_नकल(&cdev->lan_info.params, &params, माप(काष्ठा i40e_params));
	cdev->client->ops->l2_param_change(&cdev->lan_info, cdev->client,
					   &params);
पूर्ण

/**
 * i40e_client_release_qvlist - release MSI-X vector mapping क्रम client
 * @ldev: poपूर्णांकer to L2 context.
 *
 **/
अटल व्योम i40e_client_release_qvlist(काष्ठा i40e_info *ldev)
अणु
	काष्ठा i40e_qvlist_info *qvlist_info = ldev->qvlist_info;
	u32 i;

	अगर (!ldev->qvlist_info)
		वापस;

	क्रम (i = 0; i < qvlist_info->num_vectors; i++) अणु
		काष्ठा i40e_pf *pf = ldev->pf;
		काष्ठा i40e_qv_info *qv_info;
		u32 reg_idx;

		qv_info = &qvlist_info->qv_info[i];
		अगर (!qv_info)
			जारी;
		reg_idx = I40E_PFINT_LNKLSTN(qv_info->v_idx - 1);
		wr32(&pf->hw, reg_idx, I40E_PFINT_LNKLSTN_FIRSTQ_INDX_MASK);
	पूर्ण
	kमुक्त(ldev->qvlist_info);
	ldev->qvlist_info = शून्य;
पूर्ण

/**
 * i40e_notअगरy_client_of_netdev_बंद - call the client बंद callback
 * @vsi: the VSI with netdev बंदd
 * @reset: true when बंद called due to a reset pending
 *
 * If there is a client to this netdev, call the client with बंद
 **/
व्योम i40e_notअगरy_client_of_netdev_बंद(काष्ठा i40e_vsi *vsi, bool reset)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_client_instance *cdev = pf->cinst;

	अगर (!cdev || !cdev->client)
		वापस;
	अगर (!cdev->client->ops || !cdev->client->ops->बंद) अणु
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance close routine\n");
		वापस;
	पूर्ण
	cdev->client->ops->बंद(&cdev->lan_info, cdev->client, reset);
	clear_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state);
	i40e_client_release_qvlist(&cdev->lan_info);
पूर्ण

/**
 * i40e_notअगरy_client_of_vf_reset - call the client vf reset callback
 * @pf: PF device poपूर्णांकer
 * @vf_id: asolute id of VF being reset
 *
 * If there is a client attached to this PF, notअगरy when a VF is reset
 **/
व्योम i40e_notअगरy_client_of_vf_reset(काष्ठा i40e_pf *pf, u32 vf_id)
अणु
	काष्ठा i40e_client_instance *cdev = pf->cinst;

	अगर (!cdev || !cdev->client)
		वापस;
	अगर (!cdev->client->ops || !cdev->client->ops->vf_reset) अणु
		dev_dbg(&pf->pdev->dev,
			"Cannot locate client instance VF reset routine\n");
		वापस;
	पूर्ण
	अगर (!test_bit(__I40E_CLIENT_INSTANCE_OPENED,  &cdev->state)) अणु
		dev_dbg(&pf->pdev->dev, "Client is not open, abort vf-reset\n");
		वापस;
	पूर्ण
	cdev->client->ops->vf_reset(&cdev->lan_info, cdev->client, vf_id);
पूर्ण

/**
 * i40e_notअगरy_client_of_vf_enable - call the client vf notअगरication callback
 * @pf: PF device poपूर्णांकer
 * @num_vfs: the number of VFs currently enabled, 0 क्रम disable
 *
 * If there is a client attached to this PF, call its VF notअगरication routine
 **/
व्योम i40e_notअगरy_client_of_vf_enable(काष्ठा i40e_pf *pf, u32 num_vfs)
अणु
	काष्ठा i40e_client_instance *cdev = pf->cinst;

	अगर (!cdev || !cdev->client)
		वापस;
	अगर (!cdev->client->ops || !cdev->client->ops->vf_enable) अणु
		dev_dbg(&pf->pdev->dev,
			"Cannot locate client instance VF enable routine\n");
		वापस;
	पूर्ण
	अगर (!test_bit(__I40E_CLIENT_INSTANCE_OPENED,
		      &cdev->state)) अणु
		dev_dbg(&pf->pdev->dev, "Client is not open, abort vf-enable\n");
		वापस;
	पूर्ण
	cdev->client->ops->vf_enable(&cdev->lan_info, cdev->client, num_vfs);
पूर्ण

/**
 * i40e_vf_client_capable - ask the client अगर it likes the specअगरied VF
 * @pf: PF device poपूर्णांकer
 * @vf_id: the VF in question
 *
 * If there is a client of the specअगरied type attached to this PF, call
 * its vf_capable routine
 **/
पूर्णांक i40e_vf_client_capable(काष्ठा i40e_pf *pf, u32 vf_id)
अणु
	काष्ठा i40e_client_instance *cdev = pf->cinst;
	पूर्णांक capable = false;

	अगर (!cdev || !cdev->client)
		जाओ out;
	अगर (!cdev->client->ops || !cdev->client->ops->vf_capable) अणु
		dev_dbg(&pf->pdev->dev,
			"Cannot locate client instance VF capability routine\n");
		जाओ out;
	पूर्ण
	अगर (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state))
		जाओ out;

	capable = cdev->client->ops->vf_capable(&cdev->lan_info,
						cdev->client,
						vf_id);
out:
	वापस capable;
पूर्ण

व्योम i40e_client_update_msix_info(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_client_instance *cdev = pf->cinst;

	अगर (!cdev || !cdev->client)
		वापस;

	cdev->lan_info.msix_count = pf->num_iwarp_msix;
	cdev->lan_info.msix_entries = &pf->msix_entries[pf->iwarp_base_vector];
पूर्ण

/**
 * i40e_client_add_instance - add a client instance काष्ठा to the instance list
 * @pf: poपूर्णांकer to the board काष्ठा
 *
 **/
अटल व्योम i40e_client_add_instance(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_client_instance *cdev = शून्य;
	काष्ठा netdev_hw_addr *mac = शून्य;
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];

	अगर (!रेजिस्टरed_client || pf->cinst)
		वापस;

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस;

	cdev->lan_info.pf = (व्योम *)pf;
	cdev->lan_info.netdev = vsi->netdev;
	cdev->lan_info.pcidev = pf->pdev;
	cdev->lan_info.fid = pf->hw.pf_id;
	cdev->lan_info.ftype = I40E_CLIENT_FTYPE_PF;
	cdev->lan_info.hw_addr = pf->hw.hw_addr;
	cdev->lan_info.ops = &i40e_lan_ops;
	cdev->lan_info.version.major = I40E_CLIENT_VERSION_MAJOR;
	cdev->lan_info.version.minor = I40E_CLIENT_VERSION_MINOR;
	cdev->lan_info.version.build = I40E_CLIENT_VERSION_BUILD;
	cdev->lan_info.fw_maj_ver = pf->hw.aq.fw_maj_ver;
	cdev->lan_info.fw_min_ver = pf->hw.aq.fw_min_ver;
	cdev->lan_info.fw_build = pf->hw.aq.fw_build;
	set_bit(__I40E_CLIENT_INSTANCE_NONE, &cdev->state);

	अगर (i40e_client_get_params(vsi, &cdev->lan_info.params)) अणु
		kमुक्त(cdev);
		cdev = शून्य;
		वापस;
	पूर्ण

	mac = list_first_entry(&cdev->lan_info.netdev->dev_addrs.list,
			       काष्ठा netdev_hw_addr, list);
	अगर (mac)
		ether_addr_copy(cdev->lan_info.lanmac, mac->addr);
	अन्यथा
		dev_err(&pf->pdev->dev, "MAC address list is empty!\n");

	cdev->client = रेजिस्टरed_client;
	pf->cinst = cdev;

	i40e_client_update_msix_info(pf);
पूर्ण

/**
 * i40e_client_del_instance - हटाओs a client instance from the list
 * @pf: poपूर्णांकer to the board काष्ठा
 *
 **/
अटल
व्योम i40e_client_del_instance(काष्ठा i40e_pf *pf)
अणु
	kमुक्त(pf->cinst);
	pf->cinst = शून्य;
पूर्ण

/**
 * i40e_client_subtask - client मुख्यtenance work
 * @pf: board निजी काष्ठाure
 **/
व्योम i40e_client_subtask(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_client *client = रेजिस्टरed_client;
	काष्ठा i40e_client_instance *cdev;
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	पूर्णांक ret = 0;

	अगर (!test_and_clear_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state))
		वापस;
	cdev = pf->cinst;

	/* If we're करोwn or resetting, just bail */
	अगर (test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		वापस;

	अगर (!client || !cdev)
		वापस;

	/* Here we handle client खोलोs. If the client is करोwn, and
	 * the netdev is रेजिस्टरed, then खोलो the client.
	 */
	अगर (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state)) अणु
		अगर (vsi->netdev_रेजिस्टरed &&
		    client->ops && client->ops->खोलो) अणु
			set_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state);
			ret = client->ops->खोलो(&cdev->lan_info, client);
			अगर (ret) अणु
				/* Remove failed client instance */
				clear_bit(__I40E_CLIENT_INSTANCE_OPENED,
					  &cdev->state);
				i40e_client_del_instance(pf);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* enable/disable PE TCP_ENA flag based on netdev करोwn/up
	 */
	अगर (test_bit(__I40E_VSI_DOWN, vsi->state))
		i40e_client_update_vsi_ctxt(&cdev->lan_info, client,
					    0, 0, 0,
					    I40E_CLIENT_VSI_FLAG_TCP_ENABLE);
	अन्यथा
		i40e_client_update_vsi_ctxt(&cdev->lan_info, client,
					    0, 0,
					    I40E_CLIENT_VSI_FLAG_TCP_ENABLE,
					    I40E_CLIENT_VSI_FLAG_TCP_ENABLE);
पूर्ण

/**
 * i40e_lan_add_device - add a lan device काष्ठा to the list of lan devices
 * @pf: poपूर्णांकer to the board काष्ठा
 *
 * Returns 0 on success or none 0 on error
 **/
पूर्णांक i40e_lan_add_device(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_device *ldev;
	पूर्णांक ret = 0;

	mutex_lock(&i40e_device_mutex);
	list_क्रम_each_entry(ldev, &i40e_devices, list) अणु
		अगर (ldev->pf == pf) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण
	ldev = kzalloc(माप(*ldev), GFP_KERNEL);
	अगर (!ldev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ldev->pf = pf;
	INIT_LIST_HEAD(&ldev->list);
	list_add(&ldev->list, &i40e_devices);
	dev_info(&pf->pdev->dev, "Added LAN device PF%d bus=0x%02x dev=0x%02x func=0x%02x\n",
		 pf->hw.pf_id, pf->hw.bus.bus_id,
		 pf->hw.bus.device, pf->hw.bus.func);

	/* If a client has alपढ़ोy been रेजिस्टरed, we need to add an instance
	 * of it to our new LAN device.
	 */
	अगर (रेजिस्टरed_client)
		i40e_client_add_instance(pf);

	/* Since in some हालs रेजिस्टर may have happened beक्रमe a device माला_लो
	 * added, we can schedule a subtask to go initiate the clients अगर
	 * they can be launched at probe समय.
	 */
	set_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state);
	i40e_service_event_schedule(pf);

out:
	mutex_unlock(&i40e_device_mutex);
	वापस ret;
पूर्ण

/**
 * i40e_lan_del_device - हटाओs a lan device from the device list
 * @pf: poपूर्णांकer to the board काष्ठा
 *
 * Returns 0 on success or non-0 on error
 **/
पूर्णांक i40e_lan_del_device(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_device *ldev, *पंचांगp;
	पूर्णांक ret = -ENODEV;

	/* First, हटाओ any client instance. */
	i40e_client_del_instance(pf);

	mutex_lock(&i40e_device_mutex);
	list_क्रम_each_entry_safe(ldev, पंचांगp, &i40e_devices, list) अणु
		अगर (ldev->pf == pf) अणु
			dev_info(&pf->pdev->dev, "Deleted LAN device PF%d bus=0x%02x dev=0x%02x func=0x%02x\n",
				 pf->hw.pf_id, pf->hw.bus.bus_id,
				 pf->hw.bus.device, pf->hw.bus.func);
			list_del(&ldev->list);
			kमुक्त(ldev);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&i40e_device_mutex);
	वापस ret;
पूर्ण

/**
 * i40e_client_release - release client specअगरic resources
 * @client: poपूर्णांकer to the रेजिस्टरed client
 *
 **/
अटल व्योम i40e_client_release(काष्ठा i40e_client *client)
अणु
	काष्ठा i40e_client_instance *cdev;
	काष्ठा i40e_device *ldev;
	काष्ठा i40e_pf *pf;

	mutex_lock(&i40e_device_mutex);
	list_क्रम_each_entry(ldev, &i40e_devices, list) अणु
		pf = ldev->pf;
		cdev = pf->cinst;
		अगर (!cdev)
			जारी;

		जबतक (test_and_set_bit(__I40E_SERVICE_SCHED,
					pf->state))
			usleep_range(500, 1000);

		अगर (test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state)) अणु
			अगर (client->ops && client->ops->बंद)
				client->ops->बंद(&cdev->lan_info, client,
						   false);
			i40e_client_release_qvlist(&cdev->lan_info);
			clear_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state);

			dev_warn(&pf->pdev->dev,
				 "Client %s instance for PF id %d closed\n",
				 client->name, pf->hw.pf_id);
		पूर्ण
		/* delete the client instance */
		i40e_client_del_instance(pf);
		dev_info(&pf->pdev->dev, "Deleted client instance of Client %s\n",
			 client->name);
		clear_bit(__I40E_SERVICE_SCHED, pf->state);
	पूर्ण
	mutex_unlock(&i40e_device_mutex);
पूर्ण

/**
 * i40e_client_prepare - prepare client specअगरic resources
 * @client: poपूर्णांकer to the रेजिस्टरed client
 *
 **/
अटल व्योम i40e_client_prepare(काष्ठा i40e_client *client)
अणु
	काष्ठा i40e_device *ldev;
	काष्ठा i40e_pf *pf;

	mutex_lock(&i40e_device_mutex);
	list_क्रम_each_entry(ldev, &i40e_devices, list) अणु
		pf = ldev->pf;
		i40e_client_add_instance(pf);
		/* Start the client subtask */
		set_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state);
		i40e_service_event_schedule(pf);
	पूर्ण
	mutex_unlock(&i40e_device_mutex);
पूर्ण

/**
 * i40e_client_virtchnl_send - TBD
 * @ldev: poपूर्णांकer to L2 context
 * @client: Client poपूर्णांकer
 * @vf_id: असलolute VF identअगरier
 * @msg: message buffer
 * @len: length of message buffer
 *
 * Return 0 on success or < 0 on error
 **/
अटल पूर्णांक i40e_client_virtchnl_send(काष्ठा i40e_info *ldev,
				     काष्ठा i40e_client *client,
				     u32 vf_id, u8 *msg, u16 len)
अणु
	काष्ठा i40e_pf *pf = ldev->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status err;

	err = i40e_aq_send_msg_to_vf(hw, vf_id, VIRTCHNL_OP_IWARP,
				     0, msg, len, शून्य);
	अगर (err)
		dev_err(&pf->pdev->dev, "Unable to send iWarp message to VF, error %d, aq status %d\n",
			err, hw->aq.asq_last_status);

	वापस err;
पूर्ण

/**
 * i40e_client_setup_qvlist
 * @ldev: poपूर्णांकer to L2 context.
 * @client: Client poपूर्णांकer.
 * @qvlist_info: queue and vector list
 *
 * Return 0 on success or < 0 on error
 **/
अटल पूर्णांक i40e_client_setup_qvlist(काष्ठा i40e_info *ldev,
				    काष्ठा i40e_client *client,
				    काष्ठा i40e_qvlist_info *qvlist_info)
अणु
	काष्ठा i40e_pf *pf = ldev->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_qv_info *qv_info;
	u32 v_idx, i, reg_idx, reg;

	ldev->qvlist_info = kzalloc(काष्ठा_size(ldev->qvlist_info, qv_info,
				    qvlist_info->num_vectors - 1), GFP_KERNEL);
	अगर (!ldev->qvlist_info)
		वापस -ENOMEM;
	ldev->qvlist_info->num_vectors = qvlist_info->num_vectors;

	क्रम (i = 0; i < qvlist_info->num_vectors; i++) अणु
		qv_info = &qvlist_info->qv_info[i];
		अगर (!qv_info)
			जारी;
		v_idx = qv_info->v_idx;

		/* Validate vector id beदीर्घs to this client */
		अगर ((v_idx >= (pf->iwarp_base_vector + pf->num_iwarp_msix)) ||
		    (v_idx < pf->iwarp_base_vector))
			जाओ err;

		ldev->qvlist_info->qv_info[i] = *qv_info;
		reg_idx = I40E_PFINT_LNKLSTN(v_idx - 1);

		अगर (qv_info->ceq_idx == I40E_QUEUE_INVALID_IDX) अणु
			/* Special हाल - No CEQ mapped on this vector */
			wr32(hw, reg_idx, I40E_PFINT_LNKLSTN_FIRSTQ_INDX_MASK);
		पूर्ण अन्यथा अणु
			reg = (qv_info->ceq_idx &
			       I40E_PFINT_LNKLSTN_FIRSTQ_INDX_MASK) |
			       (I40E_QUEUE_TYPE_PE_CEQ <<
			       I40E_PFINT_LNKLSTN_FIRSTQ_TYPE_SHIFT);
			wr32(hw, reg_idx, reg);

			reg = (I40E_PFINT_CEQCTL_CAUSE_ENA_MASK |
			       (v_idx << I40E_PFINT_CEQCTL_MSIX_INDX_SHIFT) |
			       (qv_info->itr_idx <<
				I40E_PFINT_CEQCTL_ITR_INDX_SHIFT) |
			       (I40E_QUEUE_END_OF_LIST <<
				I40E_PFINT_CEQCTL_NEXTQ_INDX_SHIFT));
			wr32(hw, I40E_PFINT_CEQCTL(qv_info->ceq_idx), reg);
		पूर्ण
		अगर (qv_info->aeq_idx != I40E_QUEUE_INVALID_IDX) अणु
			reg = (I40E_PFINT_AEQCTL_CAUSE_ENA_MASK |
			       (v_idx << I40E_PFINT_AEQCTL_MSIX_INDX_SHIFT) |
			       (qv_info->itr_idx <<
				I40E_PFINT_AEQCTL_ITR_INDX_SHIFT));

			wr32(hw, I40E_PFINT_AEQCTL, reg);
		पूर्ण
	पूर्ण
	/* Mitigate sync problems with iwarp VF driver */
	i40e_flush(hw);
	वापस 0;
err:
	kमुक्त(ldev->qvlist_info);
	ldev->qvlist_info = शून्य;
	वापस -EINVAL;
पूर्ण

/**
 * i40e_client_request_reset
 * @ldev: poपूर्णांकer to L2 context.
 * @client: Client poपूर्णांकer.
 * @reset_level: reset level
 **/
अटल व्योम i40e_client_request_reset(काष्ठा i40e_info *ldev,
				      काष्ठा i40e_client *client,
				      u32 reset_level)
अणु
	काष्ठा i40e_pf *pf = ldev->pf;

	चयन (reset_level) अणु
	हाल I40E_CLIENT_RESET_LEVEL_PF:
		set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
		अवरोध;
	हाल I40E_CLIENT_RESET_LEVEL_CORE:
		set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
		अवरोध;
	शेष:
		dev_warn(&pf->pdev->dev,
			 "Client for PF id %d requested an unsupported reset: %d.\n",
			 pf->hw.pf_id, reset_level);
		अवरोध;
	पूर्ण

	i40e_service_event_schedule(pf);
पूर्ण

/**
 * i40e_client_update_vsi_ctxt
 * @ldev: poपूर्णांकer to L2 context.
 * @client: Client poपूर्णांकer.
 * @is_vf: अगर this क्रम the VF
 * @vf_id: अगर is_vf true this carries the vf_id
 * @flag: Any device level setting that needs to be करोne क्रम PE
 * @valid_flag: Bits in this match up and enable changing of flag bits
 *
 * Return 0 on success or < 0 on error
 **/
अटल पूर्णांक i40e_client_update_vsi_ctxt(काष्ठा i40e_info *ldev,
				       काष्ठा i40e_client *client,
				       bool is_vf, u32 vf_id,
				       u32 flag, u32 valid_flag)
अणु
	काष्ठा i40e_pf *pf = ldev->pf;
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	काष्ठा i40e_vsi_context ctxt;
	bool update = true;
	i40e_status err;

	/* TODO: क्रम now करो not allow setting VF's VSI setting */
	अगर (is_vf)
		वापस -EINVAL;

	ctxt.seid = pf->मुख्य_vsi_seid;
	ctxt.pf_num = pf->hw.pf_id;
	err = i40e_aq_get_vsi_params(&pf->hw, &ctxt, शून्य);
	ctxt.flags = I40E_AQ_VSI_TYPE_PF;
	अगर (err) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't get PF vsi config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, err),
			 i40e_aq_str(&pf->hw,
				     pf->hw.aq.asq_last_status));
		वापस -ENOENT;
	पूर्ण

	अगर ((valid_flag & I40E_CLIENT_VSI_FLAG_TCP_ENABLE) &&
	    (flag & I40E_CLIENT_VSI_FLAG_TCP_ENABLE)) अणु
		ctxt.info.valid_sections =
			cpu_to_le16(I40E_AQ_VSI_PROP_QUEUE_OPT_VALID);
		ctxt.info.queueing_opt_flags |= I40E_AQ_VSI_QUE_OPT_TCP_ENA;
	पूर्ण अन्यथा अगर ((valid_flag & I40E_CLIENT_VSI_FLAG_TCP_ENABLE) &&
		  !(flag & I40E_CLIENT_VSI_FLAG_TCP_ENABLE)) अणु
		ctxt.info.valid_sections =
			cpu_to_le16(I40E_AQ_VSI_PROP_QUEUE_OPT_VALID);
		ctxt.info.queueing_opt_flags &= ~I40E_AQ_VSI_QUE_OPT_TCP_ENA;
	पूर्ण अन्यथा अणु
		update = false;
		dev_warn(&pf->pdev->dev,
			 "Client for PF id %d request an unsupported Config: %x.\n",
			 pf->hw.pf_id, flag);
	पूर्ण

	अगर (update) अणु
		err = i40e_aq_update_vsi_params(&vsi->back->hw, &ctxt, शून्य);
		अगर (err) अणु
			dev_info(&pf->pdev->dev,
				 "update VSI ctxt for PE failed, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, err),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/**
 * i40e_रेजिस्टर_client - Register a i40e client driver with the L2 driver
 * @client: poपूर्णांकer to the i40e_client काष्ठा
 *
 * Returns 0 on success or non-0 on error
 **/
पूर्णांक i40e_रेजिस्टर_client(काष्ठा i40e_client *client)
अणु
	पूर्णांक ret = 0;

	अगर (!client) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (म_माप(client->name) == 0) अणु
		pr_info("i40e: Failed to register client with no name\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (रेजिस्टरed_client) अणु
		pr_info("i40e: Client %s has already been registered!\n",
			client->name);
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	अगर ((client->version.major != I40E_CLIENT_VERSION_MAJOR) ||
	    (client->version.minor != I40E_CLIENT_VERSION_MINOR)) अणु
		pr_info("i40e: Failed to register client %s due to mismatched client interface version\n",
			client->name);
		pr_info("Client is using version: %02d.%02d.%02d while LAN driver supports %s\n",
			client->version.major, client->version.minor,
			client->version.build,
			i40e_client_पूर्णांकerface_version_str);
		ret = -EIO;
		जाओ out;
	पूर्ण

	रेजिस्टरed_client = client;

	i40e_client_prepare(client);

	pr_info("i40e: Registered client %s\n", client->name);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(i40e_रेजिस्टर_client);

/**
 * i40e_unरेजिस्टर_client - Unरेजिस्टर a i40e client driver with the L2 driver
 * @client: poपूर्णांकer to the i40e_client काष्ठा
 *
 * Returns 0 on success or non-0 on error
 **/
पूर्णांक i40e_unरेजिस्टर_client(काष्ठा i40e_client *client)
अणु
	पूर्णांक ret = 0;

	अगर (रेजिस्टरed_client != client) अणु
		pr_info("i40e: Client %s has not been registered\n",
			client->name);
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	रेजिस्टरed_client = शून्य;
	/* When a unरेजिस्टर request comes through we would have to send
	 * a बंद क्रम each of the client instances that were खोलोed.
	 * client_release function is called to handle this.
	 */
	i40e_client_release(client);

	pr_info("i40e: Unregistered client %s\n", client->name);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(i40e_unरेजिस्टर_client);
