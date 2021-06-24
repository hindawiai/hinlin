<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>

#समावेश "pdr_internal.h"

काष्ठा pdr_service अणु
	अक्षर service_name[SERVREG_NAME_LENGTH + 1];
	अक्षर service_path[SERVREG_NAME_LENGTH + 1];

	काष्ठा sockaddr_qrtr addr;

	अचिन्हित पूर्णांक instance;
	अचिन्हित पूर्णांक service;
	u8 service_data_valid;
	u32 service_data;
	पूर्णांक state;

	bool need_notअगरier_रेजिस्टर;
	bool need_notअगरier_हटाओ;
	bool need_locator_lookup;
	bool service_connected;

	काष्ठा list_head node;
पूर्ण;

काष्ठा pdr_handle अणु
	काष्ठा qmi_handle locator_hdl;
	काष्ठा qmi_handle notअगरier_hdl;

	काष्ठा sockaddr_qrtr locator_addr;

	काष्ठा list_head lookups;
	काष्ठा list_head indack_list;

	/* control access to pdr lookup/indack lists */
	काष्ठा mutex list_lock;

	/* serialize pd status invocation */
	काष्ठा mutex status_lock;

	/* control access to the locator state */
	काष्ठा mutex lock;

	bool locator_init_complete;

	काष्ठा work_काष्ठा locator_work;
	काष्ठा work_काष्ठा notअगरier_work;
	काष्ठा work_काष्ठा indack_work;

	काष्ठा workqueue_काष्ठा *notअगरier_wq;
	काष्ठा workqueue_काष्ठा *indack_wq;

	व्योम (*status)(पूर्णांक state, अक्षर *service_path, व्योम *priv);
	व्योम *priv;
पूर्ण;

काष्ठा pdr_list_node अणु
	क्रमागत servreg_service_state curr_state;
	u16 transaction_id;
	काष्ठा pdr_service *pds;
	काष्ठा list_head node;
पूर्ण;

अटल पूर्णांक pdr_locator_new_server(काष्ठा qmi_handle *qmi,
				  काष्ठा qmi_service *svc)
अणु
	काष्ठा pdr_handle *pdr = container_of(qmi, काष्ठा pdr_handle,
					      locator_hdl);
	काष्ठा pdr_service *pds;

	/* Create a local client port क्रम QMI communication */
	pdr->locator_addr.sq_family = AF_QIPCRTR;
	pdr->locator_addr.sq_node = svc->node;
	pdr->locator_addr.sq_port = svc->port;

	mutex_lock(&pdr->lock);
	pdr->locator_init_complete = true;
	mutex_unlock(&pdr->lock);

	/* Service pending lookup requests */
	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry(pds, &pdr->lookups, node) अणु
		अगर (pds->need_locator_lookup)
			schedule_work(&pdr->locator_work);
	पूर्ण
	mutex_unlock(&pdr->list_lock);

	वापस 0;
पूर्ण

अटल व्योम pdr_locator_del_server(काष्ठा qmi_handle *qmi,
				   काष्ठा qmi_service *svc)
अणु
	काष्ठा pdr_handle *pdr = container_of(qmi, काष्ठा pdr_handle,
					      locator_hdl);

	mutex_lock(&pdr->lock);
	pdr->locator_init_complete = false;
	mutex_unlock(&pdr->lock);

	pdr->locator_addr.sq_node = 0;
	pdr->locator_addr.sq_port = 0;
पूर्ण

अटल स्थिर काष्ठा qmi_ops pdr_locator_ops = अणु
	.new_server = pdr_locator_new_server,
	.del_server = pdr_locator_del_server,
पूर्ण;

अटल पूर्णांक pdr_रेजिस्टर_listener(काष्ठा pdr_handle *pdr,
				 काष्ठा pdr_service *pds,
				 bool enable)
अणु
	काष्ठा servreg_रेजिस्टर_listener_resp resp;
	काष्ठा servreg_रेजिस्टर_listener_req req;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	ret = qmi_txn_init(&pdr->notअगरier_hdl, &txn,
			   servreg_रेजिस्टर_listener_resp_ei,
			   &resp);
	अगर (ret < 0)
		वापस ret;

	req.enable = enable;
	म_नकल(req.service_path, pds->service_path);

	ret = qmi_send_request(&pdr->notअगरier_hdl, &pds->addr,
			       &txn, SERVREG_REGISTER_LISTENER_REQ,
			       SERVREG_REGISTER_LISTENER_REQ_LEN,
			       servreg_रेजिस्टर_listener_req_ei,
			       &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		वापस ret;
	पूर्ण

	ret = qmi_txn_रुको(&txn, 5 * HZ);
	अगर (ret < 0) अणु
		pr_err("PDR: %s register listener txn wait failed: %d\n",
		       pds->service_path, ret);
		वापस ret;
	पूर्ण

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		pr_err("PDR: %s register listener failed: 0x%x\n",
		       pds->service_path, resp.resp.error);
		वापस -EREMOTEIO;
	पूर्ण

	pds->state = resp.curr_state;

	वापस 0;
पूर्ण

अटल व्योम pdr_notअगरier_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pdr_handle *pdr = container_of(work, काष्ठा pdr_handle,
					      notअगरier_work);
	काष्ठा pdr_service *pds;
	पूर्णांक ret;

	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry(pds, &pdr->lookups, node) अणु
		अगर (pds->service_connected) अणु
			अगर (!pds->need_notअगरier_रेजिस्टर)
				जारी;

			pds->need_notअगरier_रेजिस्टर = false;
			ret = pdr_रेजिस्टर_listener(pdr, pds, true);
			अगर (ret < 0)
				pds->state = SERVREG_SERVICE_STATE_DOWN;
		पूर्ण अन्यथा अणु
			अगर (!pds->need_notअगरier_हटाओ)
				जारी;

			pds->need_notअगरier_हटाओ = false;
			pds->state = SERVREG_SERVICE_STATE_DOWN;
		पूर्ण

		mutex_lock(&pdr->status_lock);
		pdr->status(pds->state, pds->service_path, pdr->priv);
		mutex_unlock(&pdr->status_lock);
	पूर्ण
	mutex_unlock(&pdr->list_lock);
पूर्ण

अटल पूर्णांक pdr_notअगरier_new_server(काष्ठा qmi_handle *qmi,
				   काष्ठा qmi_service *svc)
अणु
	काष्ठा pdr_handle *pdr = container_of(qmi, काष्ठा pdr_handle,
					      notअगरier_hdl);
	काष्ठा pdr_service *pds;

	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry(pds, &pdr->lookups, node) अणु
		अगर (pds->service == svc->service &&
		    pds->instance == svc->instance) अणु
			pds->service_connected = true;
			pds->need_notअगरier_रेजिस्टर = true;
			pds->addr.sq_family = AF_QIPCRTR;
			pds->addr.sq_node = svc->node;
			pds->addr.sq_port = svc->port;
			queue_work(pdr->notअगरier_wq, &pdr->notअगरier_work);
		पूर्ण
	पूर्ण
	mutex_unlock(&pdr->list_lock);

	वापस 0;
पूर्ण

अटल व्योम pdr_notअगरier_del_server(काष्ठा qmi_handle *qmi,
				    काष्ठा qmi_service *svc)
अणु
	काष्ठा pdr_handle *pdr = container_of(qmi, काष्ठा pdr_handle,
					      notअगरier_hdl);
	काष्ठा pdr_service *pds;

	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry(pds, &pdr->lookups, node) अणु
		अगर (pds->service == svc->service &&
		    pds->instance == svc->instance) अणु
			pds->service_connected = false;
			pds->need_notअगरier_हटाओ = true;
			pds->addr.sq_node = 0;
			pds->addr.sq_port = 0;
			queue_work(pdr->notअगरier_wq, &pdr->notअगरier_work);
		पूर्ण
	पूर्ण
	mutex_unlock(&pdr->list_lock);
पूर्ण

अटल स्थिर काष्ठा qmi_ops pdr_notअगरier_ops = अणु
	.new_server = pdr_notअगरier_new_server,
	.del_server = pdr_notअगरier_del_server,
पूर्ण;

अटल पूर्णांक pdr_send_indack_msg(काष्ठा pdr_handle *pdr, काष्ठा pdr_service *pds,
			       u16 tid)
अणु
	काष्ठा servreg_set_ack_resp resp;
	काष्ठा servreg_set_ack_req req;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	ret = qmi_txn_init(&pdr->notअगरier_hdl, &txn, servreg_set_ack_resp_ei,
			   &resp);
	अगर (ret < 0)
		वापस ret;

	req.transaction_id = tid;
	म_नकल(req.service_path, pds->service_path);

	ret = qmi_send_request(&pdr->notअगरier_hdl, &pds->addr,
			       &txn, SERVREG_SET_ACK_REQ,
			       SERVREG_SET_ACK_REQ_LEN,
			       servreg_set_ack_req_ei,
			       &req);

	/* Skip रुकोing क्रम response */
	qmi_txn_cancel(&txn);
	वापस ret;
पूर्ण

अटल व्योम pdr_indack_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pdr_handle *pdr = container_of(work, काष्ठा pdr_handle,
					      indack_work);
	काष्ठा pdr_list_node *ind, *पंचांगp;
	काष्ठा pdr_service *pds;

	list_क्रम_each_entry_safe(ind, पंचांगp, &pdr->indack_list, node) अणु
		pds = ind->pds;

		mutex_lock(&pdr->status_lock);
		pds->state = ind->curr_state;
		pdr->status(pds->state, pds->service_path, pdr->priv);
		mutex_unlock(&pdr->status_lock);

		/* Ack the indication after clients release the PD resources */
		pdr_send_indack_msg(pdr, pds, ind->transaction_id);

		mutex_lock(&pdr->list_lock);
		list_del(&ind->node);
		mutex_unlock(&pdr->list_lock);

		kमुक्त(ind);
	पूर्ण
पूर्ण

अटल व्योम pdr_indication_cb(काष्ठा qmi_handle *qmi,
			      काष्ठा sockaddr_qrtr *sq,
			      काष्ठा qmi_txn *txn, स्थिर व्योम *data)
अणु
	काष्ठा pdr_handle *pdr = container_of(qmi, काष्ठा pdr_handle,
					      notअगरier_hdl);
	स्थिर काष्ठा servreg_state_updated_ind *ind_msg = data;
	काष्ठा pdr_list_node *ind;
	काष्ठा pdr_service *pds;
	bool found = false;

	अगर (!ind_msg || !ind_msg->service_path[0] ||
	    म_माप(ind_msg->service_path) > SERVREG_NAME_LENGTH)
		वापस;

	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry(pds, &pdr->lookups, node) अणु
		अगर (म_भेद(pds->service_path, ind_msg->service_path))
			जारी;

		found = true;
		अवरोध;
	पूर्ण
	mutex_unlock(&pdr->list_lock);

	अगर (!found)
		वापस;

	pr_info("PDR: Indication received from %s, state: 0x%x, trans-id: %d\n",
		ind_msg->service_path, ind_msg->curr_state,
		ind_msg->transaction_id);

	ind = kzalloc(माप(*ind), GFP_KERNEL);
	अगर (!ind)
		वापस;

	ind->transaction_id = ind_msg->transaction_id;
	ind->curr_state = ind_msg->curr_state;
	ind->pds = pds;

	mutex_lock(&pdr->list_lock);
	list_add_tail(&ind->node, &pdr->indack_list);
	mutex_unlock(&pdr->list_lock);

	queue_work(pdr->indack_wq, &pdr->indack_work);
पूर्ण

अटल स्थिर काष्ठा qmi_msg_handler qmi_indication_handler[] = अणु
	अणु
		.type = QMI_INDICATION,
		.msg_id = SERVREG_STATE_UPDATED_IND_ID,
		.ei = servreg_state_updated_ind_ei,
		.decoded_size = माप(काष्ठा servreg_state_updated_ind),
		.fn = pdr_indication_cb,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक pdr_get_करोमुख्य_list(काष्ठा servreg_get_करोमुख्य_list_req *req,
			       काष्ठा servreg_get_करोमुख्य_list_resp *resp,
			       काष्ठा pdr_handle *pdr)
अणु
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	ret = qmi_txn_init(&pdr->locator_hdl, &txn,
			   servreg_get_करोमुख्य_list_resp_ei, resp);
	अगर (ret < 0)
		वापस ret;

	ret = qmi_send_request(&pdr->locator_hdl,
			       &pdr->locator_addr,
			       &txn, SERVREG_GET_DOMAIN_LIST_REQ,
			       SERVREG_GET_DOMAIN_LIST_REQ_MAX_LEN,
			       servreg_get_करोमुख्य_list_req_ei,
			       req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		वापस ret;
	पूर्ण

	ret = qmi_txn_रुको(&txn, 5 * HZ);
	अगर (ret < 0) अणु
		pr_err("PDR: %s get domain list txn wait failed: %d\n",
		       req->service_name, ret);
		वापस ret;
	पूर्ण

	अगर (resp->resp.result != QMI_RESULT_SUCCESS_V01) अणु
		pr_err("PDR: %s get domain list failed: 0x%x\n",
		       req->service_name, resp->resp.error);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pdr_locate_service(काष्ठा pdr_handle *pdr, काष्ठा pdr_service *pds)
अणु
	काष्ठा servreg_get_करोमुख्य_list_resp *resp;
	काष्ठा servreg_get_करोमुख्य_list_req req;
	काष्ठा servreg_location_entry *entry;
	पूर्णांक करोमुख्यs_पढ़ो = 0;
	पूर्णांक ret, i;

	resp = kzalloc(माप(*resp), GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	/* Prepare req message */
	म_नकल(req.service_name, pds->service_name);
	req.करोमुख्य_offset_valid = true;
	req.करोमुख्य_offset = 0;

	करो अणु
		req.करोमुख्य_offset = करोमुख्यs_पढ़ो;
		ret = pdr_get_करोमुख्य_list(&req, resp, pdr);
		अगर (ret < 0)
			जाओ out;

		क्रम (i = करोमुख्यs_पढ़ो; i < resp->करोमुख्य_list_len; i++) अणु
			entry = &resp->करोमुख्य_list[i];

			अगर (strnlen(entry->name, माप(entry->name)) == माप(entry->name))
				जारी;

			अगर (!म_भेद(entry->name, pds->service_path)) अणु
				pds->service_data_valid = entry->service_data_valid;
				pds->service_data = entry->service_data;
				pds->instance = entry->instance;
				जाओ out;
			पूर्ण
		पूर्ण

		/* Update ret to indicate that the service is not yet found */
		ret = -ENXIO;

		/* Always पढ़ो total_करोमुख्यs from the response msg */
		अगर (resp->करोमुख्य_list_len > resp->total_करोमुख्यs)
			resp->करोमुख्य_list_len = resp->total_करोमुख्यs;

		करोमुख्यs_पढ़ो += resp->करोमुख्य_list_len;
	पूर्ण जबतक (करोमुख्यs_पढ़ो < resp->total_करोमुख्यs);
out:
	kमुक्त(resp);
	वापस ret;
पूर्ण

अटल व्योम pdr_notअगरy_lookup_failure(काष्ठा pdr_handle *pdr,
				      काष्ठा pdr_service *pds,
				      पूर्णांक err)
अणु
	pr_err("PDR: service lookup for %s failed: %d\n",
	       pds->service_name, err);

	अगर (err == -ENXIO)
		वापस;

	list_del(&pds->node);
	pds->state = SERVREG_LOCATOR_ERR;
	mutex_lock(&pdr->status_lock);
	pdr->status(pds->state, pds->service_path, pdr->priv);
	mutex_unlock(&pdr->status_lock);
	kमुक्त(pds);
पूर्ण

अटल व्योम pdr_locator_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pdr_handle *pdr = container_of(work, काष्ठा pdr_handle,
					      locator_work);
	काष्ठा pdr_service *pds, *पंचांगp;
	पूर्णांक ret = 0;

	/* Bail out early अगर the SERVREG LOCATOR QMI service is not up */
	mutex_lock(&pdr->lock);
	अगर (!pdr->locator_init_complete) अणु
		mutex_unlock(&pdr->lock);
		pr_debug("PDR: SERVICE LOCATOR service not available\n");
		वापस;
	पूर्ण
	mutex_unlock(&pdr->lock);

	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry_safe(pds, पंचांगp, &pdr->lookups, node) अणु
		अगर (!pds->need_locator_lookup)
			जारी;

		ret = pdr_locate_service(pdr, pds);
		अगर (ret < 0) अणु
			pdr_notअगरy_lookup_failure(pdr, pds, ret);
			जारी;
		पूर्ण

		ret = qmi_add_lookup(&pdr->notअगरier_hdl, pds->service, 1,
				     pds->instance);
		अगर (ret < 0) अणु
			pdr_notअगरy_lookup_failure(pdr, pds, ret);
			जारी;
		पूर्ण

		pds->need_locator_lookup = false;
	पूर्ण
	mutex_unlock(&pdr->list_lock);
पूर्ण

/**
 * pdr_add_lookup() - रेजिस्टर a tracking request क्रम a PD
 * @pdr:		PDR client handle
 * @service_name:	service name of the tracking request
 * @service_path:	service path of the tracking request
 *
 * Registering a pdr lookup allows क्रम tracking the lअगरe cycle of the PD.
 *
 * Return: pdr_service object on success, ERR_PTR on failure. -EALREADY is
 * वापसed अगर a lookup is alपढ़ोy in progress क्रम the given service path.
 */
काष्ठा pdr_service *pdr_add_lookup(काष्ठा pdr_handle *pdr,
				   स्थिर अक्षर *service_name,
				   स्थिर अक्षर *service_path)
अणु
	काष्ठा pdr_service *pds, *पंचांगp;
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(pdr))
		वापस ERR_PTR(-EINVAL);

	अगर (!service_name || म_माप(service_name) > SERVREG_NAME_LENGTH ||
	    !service_path || म_माप(service_path) > SERVREG_NAME_LENGTH)
		वापस ERR_PTR(-EINVAL);

	pds = kzalloc(माप(*pds), GFP_KERNEL);
	अगर (!pds)
		वापस ERR_PTR(-ENOMEM);

	pds->service = SERVREG_NOTIFIER_SERVICE;
	म_नकल(pds->service_name, service_name);
	म_नकल(pds->service_path, service_path);
	pds->need_locator_lookup = true;

	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry(पंचांगp, &pdr->lookups, node) अणु
		अगर (म_भेद(पंचांगp->service_path, service_path))
			जारी;

		mutex_unlock(&pdr->list_lock);
		ret = -EALREADY;
		जाओ err;
	पूर्ण

	list_add(&pds->node, &pdr->lookups);
	mutex_unlock(&pdr->list_lock);

	schedule_work(&pdr->locator_work);

	वापस pds;
err:
	kमुक्त(pds);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(pdr_add_lookup);

/**
 * pdr_restart_pd() - restart PD
 * @pdr:	PDR client handle
 * @pds:	PD service handle
 *
 * Restarts the PD tracked by the PDR client handle क्रम a given service path.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक pdr_restart_pd(काष्ठा pdr_handle *pdr, काष्ठा pdr_service *pds)
अणु
	काष्ठा servreg_restart_pd_resp resp;
	काष्ठा servreg_restart_pd_req req = अणु 0 पूर्ण;
	काष्ठा sockaddr_qrtr addr;
	काष्ठा pdr_service *पंचांगp;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(pdr) || IS_ERR_OR_शून्य(pds))
		वापस -EINVAL;

	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry(पंचांगp, &pdr->lookups, node) अणु
		अगर (पंचांगp != pds)
			जारी;

		अगर (!pds->service_connected)
			अवरोध;

		/* Prepare req message */
		म_नकल(req.service_path, pds->service_path);
		addr = pds->addr;
		अवरोध;
	पूर्ण
	mutex_unlock(&pdr->list_lock);

	अगर (!req.service_path[0])
		वापस -EINVAL;

	ret = qmi_txn_init(&pdr->notअगरier_hdl, &txn,
			   servreg_restart_pd_resp_ei,
			   &resp);
	अगर (ret < 0)
		वापस ret;

	ret = qmi_send_request(&pdr->notअगरier_hdl, &addr,
			       &txn, SERVREG_RESTART_PD_REQ,
			       SERVREG_RESTART_PD_REQ_MAX_LEN,
			       servreg_restart_pd_req_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		वापस ret;
	पूर्ण

	ret = qmi_txn_रुको(&txn, 5 * HZ);
	अगर (ret < 0) अणु
		pr_err("PDR: %s PD restart txn wait failed: %d\n",
		       req.service_path, ret);
		वापस ret;
	पूर्ण

	/* Check response अगर PDR is disabled */
	अगर (resp.resp.result == QMI_RESULT_FAILURE_V01 &&
	    resp.resp.error == QMI_ERR_DISABLED_V01) अणु
		pr_err("PDR: %s PD restart is disabled: 0x%x\n",
		       req.service_path, resp.resp.error);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Check the response क्रम other error हाल*/
	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		pr_err("PDR: %s request for PD restart failed: 0x%x\n",
		       req.service_path, resp.resp.error);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pdr_restart_pd);

/**
 * pdr_handle_alloc() - initialize the PDR client handle
 * @status:	function to be called on PD state change
 * @priv:	handle क्रम client's use
 *
 * Initializes the PDR client handle to allow क्रम tracking/restart of PDs.
 *
 * Return: pdr_handle object on success, ERR_PTR on failure.
 */
काष्ठा pdr_handle *pdr_handle_alloc(व्योम (*status)(पूर्णांक state,
						   अक्षर *service_path,
						   व्योम *priv), व्योम *priv)
अणु
	काष्ठा pdr_handle *pdr;
	पूर्णांक ret;

	अगर (!status)
		वापस ERR_PTR(-EINVAL);

	pdr = kzalloc(माप(*pdr), GFP_KERNEL);
	अगर (!pdr)
		वापस ERR_PTR(-ENOMEM);

	pdr->status = status;
	pdr->priv = priv;

	mutex_init(&pdr->status_lock);
	mutex_init(&pdr->list_lock);
	mutex_init(&pdr->lock);

	INIT_LIST_HEAD(&pdr->lookups);
	INIT_LIST_HEAD(&pdr->indack_list);

	INIT_WORK(&pdr->locator_work, pdr_locator_work);
	INIT_WORK(&pdr->notअगरier_work, pdr_notअगरier_work);
	INIT_WORK(&pdr->indack_work, pdr_indack_work);

	pdr->notअगरier_wq = create_singlethपढ़ो_workqueue("pdr_notifier_wq");
	अगर (!pdr->notअगरier_wq) अणु
		ret = -ENOMEM;
		जाओ मुक्त_pdr_handle;
	पूर्ण

	pdr->indack_wq = alloc_ordered_workqueue("pdr_indack_wq", WQ_HIGHPRI);
	अगर (!pdr->indack_wq) अणु
		ret = -ENOMEM;
		जाओ destroy_notअगरier;
	पूर्ण

	ret = qmi_handle_init(&pdr->locator_hdl,
			      SERVREG_GET_DOMAIN_LIST_RESP_MAX_LEN,
			      &pdr_locator_ops, शून्य);
	अगर (ret < 0)
		जाओ destroy_indack;

	ret = qmi_add_lookup(&pdr->locator_hdl, SERVREG_LOCATOR_SERVICE, 1, 1);
	अगर (ret < 0)
		जाओ release_qmi_handle;

	ret = qmi_handle_init(&pdr->notअगरier_hdl,
			      SERVREG_STATE_UPDATED_IND_MAX_LEN,
			      &pdr_notअगरier_ops,
			      qmi_indication_handler);
	अगर (ret < 0)
		जाओ release_qmi_handle;

	वापस pdr;

release_qmi_handle:
	qmi_handle_release(&pdr->locator_hdl);
destroy_indack:
	destroy_workqueue(pdr->indack_wq);
destroy_notअगरier:
	destroy_workqueue(pdr->notअगरier_wq);
मुक्त_pdr_handle:
	kमुक्त(pdr);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(pdr_handle_alloc);

/**
 * pdr_handle_release() - release the PDR client handle
 * @pdr:	PDR client handle
 *
 * Cleans up pending tracking requests and releases the underlying qmi handles.
 */
व्योम pdr_handle_release(काष्ठा pdr_handle *pdr)
अणु
	काष्ठा pdr_service *pds, *पंचांगp;

	अगर (IS_ERR_OR_शून्य(pdr))
		वापस;

	mutex_lock(&pdr->list_lock);
	list_क्रम_each_entry_safe(pds, पंचांगp, &pdr->lookups, node) अणु
		list_del(&pds->node);
		kमुक्त(pds);
	पूर्ण
	mutex_unlock(&pdr->list_lock);

	cancel_work_sync(&pdr->locator_work);
	cancel_work_sync(&pdr->notअगरier_work);
	cancel_work_sync(&pdr->indack_work);

	destroy_workqueue(pdr->notअगरier_wq);
	destroy_workqueue(pdr->indack_wq);

	qmi_handle_release(&pdr->locator_hdl);
	qmi_handle_release(&pdr->notअगरier_hdl);

	kमुक्त(pdr);
पूर्ण
EXPORT_SYMBOL(pdr_handle_release);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm Protection Domain Restart helpers");
