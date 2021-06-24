<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2013-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/qrtr.h>
#समावेश <linux/soc/qcom/qmi.h>

#समावेश "ipa.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_mem.h"
#समावेश "ipa_table.h"
#समावेश "ipa_modem.h"
#समावेश "ipa_qmi_msg.h"

/**
 * DOC: AP/Modem QMI Handshake
 *
 * The AP and modem perक्रमm a "handshake" at initialization समय to ensure
 * both sides know when everything is पढ़ोy to begin operating.  The AP
 * driver (this code) uses two QMI handles (endpoपूर्णांकs) क्रम this; a client
 * using a service on the modem, and server to service modem requests (and
 * to supply an indication message from the AP).  Once the handshake is
 * complete, the AP and modem may begin IPA operation.  This occurs
 * only when the AP IPA driver, modem IPA driver, and IPA microcontroller
 * are पढ़ोy.
 *
 * The QMI service on the modem expects to receive an INIT_DRIVER request from
 * the AP, which contains parameters used by the modem during initialization.
 * The AP sends this request as soon as it is knows the modem side service
 * is available.  The modem responds to this request, and अगर this response
 * contains a success result, the AP knows the modem IPA driver is पढ़ोy.
 *
 * The modem is responsible क्रम loading firmware on the IPA microcontroller.
 * This occurs only during the initial modem boot.  The modem sends a
 * separate DRIVER_INIT_COMPLETE request to the AP to report that the
 * microcontroller is पढ़ोy.  The AP may assume the microcontroller is
 * पढ़ोy and reमुख्य so (even अगर the modem reboots) once it has received
 * and responded to this request.
 *
 * There is one final exchange involved in the handshake.  It is required
 * on the initial modem boot, but optional (but in practice करोes occur) on
 * subsequent boots.  The modem expects to receive a final INIT_COMPLETE
 * indication message from the AP when it is about to begin its normal
 * operation.  The AP will only send this message after it has received
 * and responded to an INDICATION_REGISTER request from the modem.
 *
 * So in summary:
 * - Whenever the AP learns the modem has booted and its IPA QMI service
 *   is available, it sends an INIT_DRIVER request to the modem.  The
 *   modem supplies a success response when it is पढ़ोy to operate.
 * - On the initial boot, the modem sets up the IPA microcontroller, and
 *   sends a DRIVER_INIT_COMPLETE request to the AP when this is करोne.
 * - When the modem is पढ़ोy to receive an INIT_COMPLETE indication from
 *   the AP, it sends an INDICATION_REGISTER request to the AP.
 * - On the initial modem boot, everything is पढ़ोy when:
 *	- AP has received a success response from its INIT_DRIVER request
 *	- AP has responded to a DRIVER_INIT_COMPLETE request
 *	- AP has responded to an INDICATION_REGISTER request from the modem
 *	- AP has sent an INIT_COMPLETE indication to the modem
 * - On subsequent modem boots, everything is पढ़ोy when:
 *	- AP has received a success response from its INIT_DRIVER request
 *	- AP has responded to a DRIVER_INIT_COMPLETE request
 * - The INDICATION_REGISTER request and INIT_COMPLETE indication are
 *   optional क्रम non-initial modem boots, and have no bearing on the
 *   determination of when things are "ready"
 */

#घोषणा IPA_HOST_SERVICE_SVC_ID		0x31
#घोषणा IPA_HOST_SVC_VERS		1
#घोषणा IPA_HOST_SERVICE_INS_ID		1

#घोषणा IPA_MODEM_SERVICE_SVC_ID	0x31
#घोषणा IPA_MODEM_SERVICE_INS_ID	2
#घोषणा IPA_MODEM_SVC_VERS		1

#घोषणा QMI_INIT_DRIVER_TIMEOUT		60000	/* A minute in milliseconds */

/* Send an INIT_COMPLETE indication message to the modem */
अटल व्योम ipa_server_init_complete(काष्ठा ipa_qmi *ipa_qmi)
अणु
	काष्ठा ipa *ipa = container_of(ipa_qmi, काष्ठा ipa, qmi);
	काष्ठा qmi_handle *qmi = &ipa_qmi->server_handle;
	काष्ठा sockaddr_qrtr *sq = &ipa_qmi->modem_sq;
	काष्ठा ipa_init_complete_ind ind = अणु पूर्ण;
	पूर्णांक ret;

	ind.status.result = QMI_RESULT_SUCCESS_V01;
	ind.status.error = QMI_ERR_NONE_V01;

	ret = qmi_send_indication(qmi, sq, IPA_QMI_INIT_COMPLETE,
				   IPA_QMI_INIT_COMPLETE_IND_SZ,
				   ipa_init_complete_ind_ei, &ind);
	अगर (ret)
		dev_err(&ipa->pdev->dev,
			"error %d sending init complete indication\n", ret);
	अन्यथा
		ipa_qmi->indication_sent = true;
पूर्ण

/* If requested (and not alपढ़ोy sent) send the INIT_COMPLETE indication */
अटल व्योम ipa_qmi_indication(काष्ठा ipa_qmi *ipa_qmi)
अणु
	अगर (!ipa_qmi->indication_requested)
		वापस;

	अगर (ipa_qmi->indication_sent)
		वापस;

	ipa_server_init_complete(ipa_qmi);
पूर्ण

/* Determine whether everything is पढ़ोy to start normal operation.
 * We know everything (अन्यथा) is पढ़ोy when we know the IPA driver on
 * the modem is पढ़ोy, and the microcontroller is पढ़ोy.
 *
 * When the modem boots (or reboots), the handshake sequence starts
 * with the AP sending the modem an INIT_DRIVER request.  Within
 * that request, the uc_loaded flag will be zero (false) क्रम an
 * initial boot, non-zero (true) क्रम a subsequent (SSR) boot.
 */
अटल व्योम ipa_qmi_पढ़ोy(काष्ठा ipa_qmi *ipa_qmi)
अणु
	काष्ठा ipa *ipa = container_of(ipa_qmi, काष्ठा ipa, qmi);
	पूर्णांक ret;

	/* We aren't पढ़ोy until the modem and microcontroller are */
	अगर (!ipa_qmi->modem_पढ़ोy || !ipa_qmi->uc_पढ़ोy)
		वापस;

	/* Send the indication message अगर it was requested */
	ipa_qmi_indication(ipa_qmi);

	/* The initial boot requires us to send the indication. */
	अगर (ipa_qmi->initial_boot) अणु
		अगर (!ipa_qmi->indication_sent)
			वापस;

		/* The initial modem boot completed successfully */
		ipa_qmi->initial_boot = false;
	पूर्ण

	/* We're पढ़ोy.  Start up normal operation */
	ipa = container_of(ipa_qmi, काष्ठा ipa, qmi);
	ret = ipa_modem_start(ipa);
	अगर (ret)
		dev_err(&ipa->pdev->dev, "error %d starting modem\n", ret);
पूर्ण

/* All QMI clients from the modem node are gone (modem shut करोwn or crashed). */
अटल व्योम ipa_server_bye(काष्ठा qmi_handle *qmi, अचिन्हित पूर्णांक node)
अणु
	काष्ठा ipa_qmi *ipa_qmi;

	ipa_qmi = container_of(qmi, काष्ठा ipa_qmi, server_handle);

	/* The modem client and server go away at the same समय */
	स_रखो(&ipa_qmi->modem_sq, 0, माप(ipa_qmi->modem_sq));

	/* initial_boot करोesn't change when modem reboots */
	/* uc_पढ़ोy करोesn't change when modem reboots */
	ipa_qmi->modem_पढ़ोy = false;
	ipa_qmi->indication_requested = false;
	ipa_qmi->indication_sent = false;
पूर्ण

अटल स्थिर काष्ठा qmi_ops ipa_server_ops = अणु
	.bye		= ipa_server_bye,
पूर्ण;

/* Callback function to handle an INDICATION_REGISTER request message from the
 * modem.  This inक्रमms the AP that the modem is now पढ़ोy to receive the
 * INIT_COMPLETE indication message.
 */
अटल व्योम ipa_server_indication_रेजिस्टर(काष्ठा qmi_handle *qmi,
					   काष्ठा sockaddr_qrtr *sq,
					   काष्ठा qmi_txn *txn,
					   स्थिर व्योम *decoded)
अणु
	काष्ठा ipa_indication_रेजिस्टर_rsp rsp = अणु पूर्ण;
	काष्ठा ipa_qmi *ipa_qmi;
	काष्ठा ipa *ipa;
	पूर्णांक ret;

	ipa_qmi = container_of(qmi, काष्ठा ipa_qmi, server_handle);
	ipa = container_of(ipa_qmi, काष्ठा ipa, qmi);

	rsp.rsp.result = QMI_RESULT_SUCCESS_V01;
	rsp.rsp.error = QMI_ERR_NONE_V01;

	ret = qmi_send_response(qmi, sq, txn, IPA_QMI_INDICATION_REGISTER,
				IPA_QMI_INDICATION_REGISTER_RSP_SZ,
				ipa_indication_रेजिस्टर_rsp_ei, &rsp);
	अगर (!ret) अणु
		ipa_qmi->indication_requested = true;
		ipa_qmi_पढ़ोy(ipa_qmi);		/* We might be पढ़ोy now */
	पूर्ण अन्यथा अणु
		dev_err(&ipa->pdev->dev,
			"error %d sending register indication response\n", ret);
	पूर्ण
पूर्ण

/* Respond to a DRIVER_INIT_COMPLETE request message from the modem. */
अटल व्योम ipa_server_driver_init_complete(काष्ठा qmi_handle *qmi,
					    काष्ठा sockaddr_qrtr *sq,
					    काष्ठा qmi_txn *txn,
					    स्थिर व्योम *decoded)
अणु
	काष्ठा ipa_driver_init_complete_rsp rsp = अणु पूर्ण;
	काष्ठा ipa_qmi *ipa_qmi;
	काष्ठा ipa *ipa;
	पूर्णांक ret;

	ipa_qmi = container_of(qmi, काष्ठा ipa_qmi, server_handle);
	ipa = container_of(ipa_qmi, काष्ठा ipa, qmi);

	rsp.rsp.result = QMI_RESULT_SUCCESS_V01;
	rsp.rsp.error = QMI_ERR_NONE_V01;

	ret = qmi_send_response(qmi, sq, txn, IPA_QMI_DRIVER_INIT_COMPLETE,
				IPA_QMI_DRIVER_INIT_COMPLETE_RSP_SZ,
				ipa_driver_init_complete_rsp_ei, &rsp);
	अगर (!ret) अणु
		ipa_qmi->uc_पढ़ोy = true;
		ipa_qmi_पढ़ोy(ipa_qmi);		/* We might be पढ़ोy now */
	पूर्ण अन्यथा अणु
		dev_err(&ipa->pdev->dev,
			"error %d sending init complete response\n", ret);
	पूर्ण
पूर्ण

/* The server handles two request message types sent by the modem. */
अटल स्थिर काष्ठा qmi_msg_handler ipa_server_msg_handlers[] = अणु
	अणु
		.type		= QMI_REQUEST,
		.msg_id		= IPA_QMI_INDICATION_REGISTER,
		.ei		= ipa_indication_रेजिस्टर_req_ei,
		.decoded_size	= IPA_QMI_INDICATION_REGISTER_REQ_SZ,
		.fn		= ipa_server_indication_रेजिस्टर,
	पूर्ण,
	अणु
		.type		= QMI_REQUEST,
		.msg_id		= IPA_QMI_DRIVER_INIT_COMPLETE,
		.ei		= ipa_driver_init_complete_req_ei,
		.decoded_size	= IPA_QMI_DRIVER_INIT_COMPLETE_REQ_SZ,
		.fn		= ipa_server_driver_init_complete,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* Handle an INIT_DRIVER response message from the modem. */
अटल व्योम ipa_client_init_driver(काष्ठा qmi_handle *qmi,
				   काष्ठा sockaddr_qrtr *sq,
				   काष्ठा qmi_txn *txn, स्थिर व्योम *decoded)
अणु
	txn->result = 0;	/* IPA_QMI_INIT_DRIVER request was successful */
	complete(&txn->completion);
पूर्ण

/* The client handles one response message type sent by the modem. */
अटल स्थिर काष्ठा qmi_msg_handler ipa_client_msg_handlers[] = अणु
	अणु
		.type		= QMI_RESPONSE,
		.msg_id		= IPA_QMI_INIT_DRIVER,
		.ei		= ipa_init_modem_driver_rsp_ei,
		.decoded_size	= IPA_QMI_INIT_DRIVER_RSP_SZ,
		.fn		= ipa_client_init_driver,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* Return a poपूर्णांकer to an init modem driver request काष्ठाure, which contains
 * configuration parameters क्रम the modem.  The modem may be started multiple
 * बार, but generally these parameters करोn't change so we can reuse the
 * request काष्ठाure once it's initialized.  The only exception is the
 * skip_uc_load field, which will be set only after the microcontroller has
 * reported it has completed its initialization.
 */
अटल स्थिर काष्ठा ipa_init_modem_driver_req *
init_modem_driver_req(काष्ठा ipa_qmi *ipa_qmi)
अणु
	काष्ठा ipa *ipa = container_of(ipa_qmi, काष्ठा ipa, qmi);
	अटल काष्ठा ipa_init_modem_driver_req req;
	स्थिर काष्ठा ipa_mem *mem;

	/* The microcontroller is initialized on the first boot */
	req.skip_uc_load_valid = 1;
	req.skip_uc_load = ipa->uc_loaded ? 1 : 0;

	/* We only have to initialize most of it once */
	अगर (req.platक्रमm_type_valid)
		वापस &req;

	req.platक्रमm_type_valid = 1;
	req.platक्रमm_type = IPA_QMI_PLATFORM_TYPE_MSM_ANDROID;

	mem = &ipa->mem[IPA_MEM_MODEM_HEADER];
	अगर (mem->size) अणु
		req.hdr_tbl_info_valid = 1;
		req.hdr_tbl_info.start = ipa->mem_offset + mem->offset;
		req.hdr_tbl_info.end = req.hdr_tbl_info.start + mem->size - 1;
	पूर्ण

	mem = &ipa->mem[IPA_MEM_V4_ROUTE];
	req.v4_route_tbl_info_valid = 1;
	req.v4_route_tbl_info.start = ipa->mem_offset + mem->offset;
	req.v4_route_tbl_info.count = mem->size / माप(__le64);

	mem = &ipa->mem[IPA_MEM_V6_ROUTE];
	req.v6_route_tbl_info_valid = 1;
	req.v6_route_tbl_info.start = ipa->mem_offset + mem->offset;
	req.v6_route_tbl_info.count = mem->size / माप(__le64);

	mem = &ipa->mem[IPA_MEM_V4_FILTER];
	req.v4_filter_tbl_start_valid = 1;
	req.v4_filter_tbl_start = ipa->mem_offset + mem->offset;

	mem = &ipa->mem[IPA_MEM_V6_FILTER];
	req.v6_filter_tbl_start_valid = 1;
	req.v6_filter_tbl_start = ipa->mem_offset + mem->offset;

	mem = &ipa->mem[IPA_MEM_MODEM];
	अगर (mem->size) अणु
		req.modem_mem_info_valid = 1;
		req.modem_mem_info.start = ipa->mem_offset + mem->offset;
		req.modem_mem_info.size = mem->size;
	पूर्ण

	req.ctrl_comm_dest_end_pt_valid = 1;
	req.ctrl_comm_dest_end_pt =
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_RX]->endpoपूर्णांक_id;

	/* skip_uc_load_valid and skip_uc_load are set above */

	mem = &ipa->mem[IPA_MEM_MODEM_PROC_CTX];
	अगर (mem->size) अणु
		req.hdr_proc_ctx_tbl_info_valid = 1;
		req.hdr_proc_ctx_tbl_info.start =
			ipa->mem_offset + mem->offset;
		req.hdr_proc_ctx_tbl_info.end =
			req.hdr_proc_ctx_tbl_info.start + mem->size - 1;
	पूर्ण

	/* Nothing to report क्रम the compression table (zip_tbl_info) */

	mem = &ipa->mem[IPA_MEM_V4_ROUTE_HASHED];
	अगर (mem->size) अणु
		req.v4_hash_route_tbl_info_valid = 1;
		req.v4_hash_route_tbl_info.start =
				ipa->mem_offset + mem->offset;
		req.v4_hash_route_tbl_info.count = mem->size / माप(__le64);
	पूर्ण

	mem = &ipa->mem[IPA_MEM_V6_ROUTE_HASHED];
	अगर (mem->size) अणु
		req.v6_hash_route_tbl_info_valid = 1;
		req.v6_hash_route_tbl_info.start =
			ipa->mem_offset + mem->offset;
		req.v6_hash_route_tbl_info.count = mem->size / माप(__le64);
	पूर्ण

	mem = &ipa->mem[IPA_MEM_V4_FILTER_HASHED];
	अगर (mem->size) अणु
		req.v4_hash_filter_tbl_start_valid = 1;
		req.v4_hash_filter_tbl_start = ipa->mem_offset + mem->offset;
	पूर्ण

	mem = &ipa->mem[IPA_MEM_V6_FILTER_HASHED];
	अगर (mem->size) अणु
		req.v6_hash_filter_tbl_start_valid = 1;
		req.v6_hash_filter_tbl_start = ipa->mem_offset + mem->offset;
	पूर्ण

	/* None of the stats fields are valid (IPA v4.0 and above) */

	अगर (ipa->version >= IPA_VERSION_4_0) अणु
		mem = &ipa->mem[IPA_MEM_STATS_QUOTA_MODEM];
		अगर (mem->size) अणु
			req.hw_stats_quota_base_addr_valid = 1;
			req.hw_stats_quota_base_addr =
				ipa->mem_offset + mem->offset;
			req.hw_stats_quota_size_valid = 1;
			req.hw_stats_quota_size = ipa->mem_offset + mem->size;
		पूर्ण

		mem = &ipa->mem[IPA_MEM_STATS_DROP];
		अगर (mem->size) अणु
			req.hw_stats_drop_base_addr_valid = 1;
			req.hw_stats_drop_base_addr =
				ipa->mem_offset + mem->offset;
			req.hw_stats_drop_size_valid = 1;
			req.hw_stats_drop_size = ipa->mem_offset + mem->size;
		पूर्ण
	पूर्ण

	वापस &req;
पूर्ण

/* Send an INIT_DRIVER request to the modem, and रुको क्रम it to complete. */
अटल व्योम ipa_client_init_driver_work(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(QMI_INIT_DRIVER_TIMEOUT);
	स्थिर काष्ठा ipa_init_modem_driver_req *req;
	काष्ठा ipa_qmi *ipa_qmi;
	काष्ठा qmi_handle *qmi;
	काष्ठा qmi_txn txn;
	काष्ठा device *dev;
	काष्ठा ipa *ipa;
	पूर्णांक ret;

	ipa_qmi = container_of(work, काष्ठा ipa_qmi, init_driver_work);
	qmi = &ipa_qmi->client_handle;

	ipa = container_of(ipa_qmi, काष्ठा ipa, qmi);
	dev = &ipa->pdev->dev;

	ret = qmi_txn_init(qmi, &txn, शून्य, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "error %d preparing init driver request\n", ret);
		वापस;
	पूर्ण

	/* Send the request, and अगर successful रुको क्रम its response */
	req = init_modem_driver_req(ipa_qmi);
	ret = qmi_send_request(qmi, &ipa_qmi->modem_sq, &txn,
			       IPA_QMI_INIT_DRIVER, IPA_QMI_INIT_DRIVER_REQ_SZ,
			       ipa_init_modem_driver_req_ei, req);
	अगर (ret)
		dev_err(dev, "error %d sending init driver request\n", ret);
	अन्यथा अगर ((ret = qmi_txn_रुको(&txn, समयout)))
		dev_err(dev, "error %d awaiting init driver response\n", ret);

	अगर (!ret) अणु
		ipa_qmi->modem_पढ़ोy = true;
		ipa_qmi_पढ़ोy(ipa_qmi);		/* We might be पढ़ोy now */
	पूर्ण अन्यथा अणु
		/* If any error occurs we need to cancel the transaction */
		qmi_txn_cancel(&txn);
	पूर्ण
पूर्ण

/* The modem server is now available.  We will send an INIT_DRIVER request
 * to the modem, but can't रुको क्रम it to complete in this callback thपढ़ो.
 * Schedule a worker on the global workqueue to करो that क्रम us.
 */
अटल पूर्णांक
ipa_client_new_server(काष्ठा qmi_handle *qmi, काष्ठा qmi_service *svc)
अणु
	काष्ठा ipa_qmi *ipa_qmi;

	ipa_qmi = container_of(qmi, काष्ठा ipa_qmi, client_handle);

	ipa_qmi->modem_sq.sq_family = AF_QIPCRTR;
	ipa_qmi->modem_sq.sq_node = svc->node;
	ipa_qmi->modem_sq.sq_port = svc->port;

	schedule_work(&ipa_qmi->init_driver_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qmi_ops ipa_client_ops = अणु
	.new_server	= ipa_client_new_server,
पूर्ण;

/* This is called by ipa_setup().  We can be inक्रमmed via remoteproc that
 * the modem has shut करोwn, in which हाल this function will be called
 * again to prepare क्रम it coming back up again.
 */
पूर्णांक ipa_qmi_setup(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_qmi *ipa_qmi = &ipa->qmi;
	पूर्णांक ret;

	ipa_qmi->initial_boot = true;

	/* The server handle is used to handle the DRIVER_INIT_COMPLETE
	 * request on the first modem boot.  It also receives the
	 * INDICATION_REGISTER request on the first boot and (optionally)
	 * subsequent boots.  The INIT_COMPLETE indication message is
	 * sent over the server handle अगर requested.
	 */
	ret = qmi_handle_init(&ipa_qmi->server_handle,
			      IPA_QMI_SERVER_MAX_RCV_SZ, &ipa_server_ops,
			      ipa_server_msg_handlers);
	अगर (ret)
		वापस ret;

	ret = qmi_add_server(&ipa_qmi->server_handle, IPA_HOST_SERVICE_SVC_ID,
			     IPA_HOST_SVC_VERS, IPA_HOST_SERVICE_INS_ID);
	अगर (ret)
		जाओ err_server_handle_release;

	/* The client handle is only used क्रम sending an INIT_DRIVER request
	 * to the modem, and receiving its response message.
	 */
	ret = qmi_handle_init(&ipa_qmi->client_handle,
			      IPA_QMI_CLIENT_MAX_RCV_SZ, &ipa_client_ops,
			      ipa_client_msg_handlers);
	अगर (ret)
		जाओ err_server_handle_release;

	/* We need this पढ़ोy beक्रमe the service lookup is added */
	INIT_WORK(&ipa_qmi->init_driver_work, ipa_client_init_driver_work);

	ret = qmi_add_lookup(&ipa_qmi->client_handle, IPA_MODEM_SERVICE_SVC_ID,
			     IPA_MODEM_SVC_VERS, IPA_MODEM_SERVICE_INS_ID);
	अगर (ret)
		जाओ err_client_handle_release;

	वापस 0;

err_client_handle_release:
	/* Releasing the handle also हटाओs रेजिस्टरed lookups */
	qmi_handle_release(&ipa_qmi->client_handle);
	स_रखो(&ipa_qmi->client_handle, 0, माप(ipa_qmi->client_handle));
err_server_handle_release:
	/* Releasing the handle also हटाओs रेजिस्टरed services */
	qmi_handle_release(&ipa_qmi->server_handle);
	स_रखो(&ipa_qmi->server_handle, 0, माप(ipa_qmi->server_handle));

	वापस ret;
पूर्ण

व्योम ipa_qmi_tearकरोwn(काष्ठा ipa *ipa)
अणु
	cancel_work_sync(&ipa->qmi.init_driver_work);

	qmi_handle_release(&ipa->qmi.client_handle);
	स_रखो(&ipa->qmi.client_handle, 0, माप(ipa->qmi.client_handle));

	qmi_handle_release(&ipa->qmi.server_handle);
	स_रखो(&ipa->qmi.server_handle, 0, माप(ipa->qmi.server_handle));
पूर्ण
