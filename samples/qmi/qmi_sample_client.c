<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sample in-kernel QMI client driver
 *
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/qrtr.h>
#समावेश <linux/net.h>
#समावेश <linux/completion.h>
#समावेश <linux/idr.h>
#समावेश <linux/माला.स>
#समावेश <net/sock.h>
#समावेश <linux/soc/qcom/qmi.h>

#घोषणा PING_REQ1_TLV_TYPE		0x1
#घोषणा PING_RESP1_TLV_TYPE		0x2
#घोषणा PING_OPT1_TLV_TYPE		0x10
#घोषणा PING_OPT2_TLV_TYPE		0x11

#घोषणा DATA_REQ1_TLV_TYPE		0x1
#घोषणा DATA_RESP1_TLV_TYPE		0x2
#घोषणा DATA_OPT1_TLV_TYPE		0x10
#घोषणा DATA_OPT2_TLV_TYPE		0x11

#घोषणा TEST_MED_DATA_SIZE_V01		8192
#घोषणा TEST_MAX_NAME_SIZE_V01		255

#घोषणा TEST_PING_REQ_MSG_ID_V01	0x20
#घोषणा TEST_DATA_REQ_MSG_ID_V01	0x21

#घोषणा TEST_PING_REQ_MAX_MSG_LEN_V01	266
#घोषणा TEST_DATA_REQ_MAX_MSG_LEN_V01	8456

काष्ठा test_name_type_v01 अणु
	u32 name_len;
	अक्षर name[TEST_MAX_NAME_SIZE_V01];
पूर्ण;

अटल काष्ठा qmi_elem_info test_name_type_v01_ei[] = अणु
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_name_type_v01,
					   name_len),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= TEST_MAX_NAME_SIZE_V01,
		.elem_size	= माप(अक्षर),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_name_type_v01,
					   name),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा test_ping_req_msg_v01 अणु
	अक्षर ping[4];

	u8 client_name_valid;
	काष्ठा test_name_type_v01 client_name;
पूर्ण;

अटल काष्ठा qmi_elem_info test_ping_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 4,
		.elem_size	= माप(अक्षर),
		.array_type	= STATIC_ARRAY,
		.tlv_type	= PING_REQ1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_ping_req_msg_v01,
					   ping),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= PING_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_ping_req_msg_v01,
					   client_name_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा test_name_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= PING_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_ping_req_msg_v01,
					   client_name),
		.ei_array	= test_name_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा test_ping_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;

	u8 pong_valid;
	अक्षर pong[4];

	u8 service_name_valid;
	काष्ठा test_name_type_v01 service_name;
पूर्ण;

अटल काष्ठा qmi_elem_info test_ping_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= PING_RESP1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_ping_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= PING_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_ping_resp_msg_v01,
					   pong_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 4,
		.elem_size	= माप(अक्षर),
		.array_type	= STATIC_ARRAY,
		.tlv_type	= PING_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_ping_resp_msg_v01,
					   pong),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= PING_OPT2_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_ping_resp_msg_v01,
					   service_name_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा test_name_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= PING_OPT2_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_ping_resp_msg_v01,
					   service_name),
		.ei_array	= test_name_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा test_data_req_msg_v01 अणु
	u32 data_len;
	u8 data[TEST_MED_DATA_SIZE_V01];

	u8 client_name_valid;
	काष्ठा test_name_type_v01 client_name;
पूर्ण;

अटल काष्ठा qmi_elem_info test_data_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= DATA_REQ1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_req_msg_v01,
					   data_len),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= TEST_MED_DATA_SIZE_V01,
		.elem_size	= माप(u8),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= DATA_REQ1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_req_msg_v01,
					   data),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= DATA_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_req_msg_v01,
					   client_name_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा test_name_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= DATA_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_req_msg_v01,
					   client_name),
		.ei_array	= test_name_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा test_data_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;

	u8 data_valid;
	u32 data_len;
	u8 data[TEST_MED_DATA_SIZE_V01];

	u8 service_name_valid;
	काष्ठा test_name_type_v01 service_name;
पूर्ण;

अटल काष्ठा qmi_elem_info test_data_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= DATA_RESP1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= DATA_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_resp_msg_v01,
					   data_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= DATA_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_resp_msg_v01,
					   data_len),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= TEST_MED_DATA_SIZE_V01,
		.elem_size	= माप(u8),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= DATA_OPT1_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_resp_msg_v01,
					   data),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= DATA_OPT2_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_resp_msg_v01,
					   service_name_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा test_name_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= DATA_OPT2_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा test_data_resp_msg_v01,
					   service_name),
		.ei_array	= test_name_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * ping_ग_लिखो() - ping_pong debugfs file ग_लिखो handler
 * @file:	debugfs file context
 * @user_buf:	reference to the user data (ignored)
 * @count:	number of bytes in @user_buf
 * @ppos:	offset in @file to ग_लिखो
 *
 * This function allows user space to send out a ping_pong QMI encoded message
 * to the associated remote test service and will वापस with the result of the
 * transaction. It serves as an example of how to provide a custom response
 * handler.
 *
 * Return: @count, or negative त्रुटि_सं on failure.
 */
अटल sमाप_प्रकार ping_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा qmi_handle *qmi = file->निजी_data;
	काष्ठा test_ping_req_msg_v01 req = अणुपूर्ण;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	स_नकल(req.ping, "ping", माप(req.ping));

	ret = qmi_txn_init(qmi, &txn, शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = qmi_send_request(qmi, शून्य, &txn,
			       TEST_PING_REQ_MSG_ID_V01,
			       TEST_PING_REQ_MAX_MSG_LEN_V01,
			       test_ping_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		वापस ret;
	पूर्ण

	ret = qmi_txn_रुको(&txn, 5 * HZ);
	अगर (ret < 0)
		count = ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations ping_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = ping_ग_लिखो,
पूर्ण;

अटल व्योम ping_pong_cb(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			 काष्ठा qmi_txn *txn, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा test_ping_resp_msg_v01 *resp = data;

	अगर (!txn) अणु
		pr_err("spurious ping response\n");
		वापस;
	पूर्ण

	अगर (resp->resp.result == QMI_RESULT_FAILURE_V01)
		txn->result = -ENXIO;
	अन्यथा अगर (!resp->pong_valid || स_भेद(resp->pong, "pong", 4))
		txn->result = -EINVAL;

	complete(&txn->completion);
पूर्ण

/*
 * data_ग_लिखो() - data debugfs file ग_लिखो handler
 * @file:	debugfs file context
 * @user_buf:	reference to the user data
 * @count:	number of bytes in @user_buf
 * @ppos:	offset in @file to ग_लिखो
 *
 * This function allows user space to send out a data QMI encoded message to
 * the associated remote test service and will वापस with the result of the
 * transaction. It serves as an example of how to have the QMI helpers decode a
 * transaction response पूर्णांकo a provided object स्वतःmatically.
 *
 * Return: @count, or negative त्रुटि_सं on failure.
 */
अटल sमाप_प्रकार data_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)

अणु
	काष्ठा qmi_handle *qmi = file->निजी_data;
	काष्ठा test_data_resp_msg_v01 *resp;
	काष्ठा test_data_req_msg_v01 *req;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	resp = kzalloc(माप(*resp), GFP_KERNEL);
	अगर (!resp) अणु
		kमुक्त(req);
		वापस -ENOMEM;
	पूर्ण

	req->data_len = min_t(माप_प्रकार, माप(req->data), count);
	अगर (copy_from_user(req->data, user_buf, req->data_len)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = qmi_txn_init(qmi, &txn, test_data_resp_msg_v01_ei, resp);
	अगर (ret < 0)
		जाओ out;

	ret = qmi_send_request(qmi, शून्य, &txn,
			       TEST_DATA_REQ_MSG_ID_V01,
			       TEST_DATA_REQ_MAX_MSG_LEN_V01,
			       test_data_req_msg_v01_ei, req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, 5 * HZ);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (!resp->data_valid ||
		   resp->data_len != req->data_len ||
		   स_भेद(resp->data, req->data, req->data_len)) अणु
		pr_err("response data doesn't match expectation\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = count;

out:
	kमुक्त(resp);
	kमुक्त(req);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations data_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = data_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा qmi_msg_handler qmi_sample_handlers[] = अणु
	अणु
		.type = QMI_RESPONSE,
		.msg_id = TEST_PING_REQ_MSG_ID_V01,
		.ei = test_ping_resp_msg_v01_ei,
		.decoded_size = माप(काष्ठा test_ping_req_msg_v01),
		.fn = ping_pong_cb
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_sample अणु
	काष्ठा qmi_handle qmi;

	काष्ठा dentry *de_dir;
	काष्ठा dentry *de_data;
	काष्ठा dentry *de_ping;
पूर्ण;

अटल काष्ठा dentry *qmi_debug_dir;

अटल पूर्णांक qmi_sample_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sockaddr_qrtr *sq;
	काष्ठा qmi_sample *sample;
	अक्षर path[20];
	पूर्णांक ret;

	sample = devm_kzalloc(&pdev->dev, माप(*sample), GFP_KERNEL);
	अगर (!sample)
		वापस -ENOMEM;

	ret = qmi_handle_init(&sample->qmi, TEST_DATA_REQ_MAX_MSG_LEN_V01,
			      शून्य,
			      qmi_sample_handlers);
	अगर (ret < 0)
		वापस ret;

	sq = dev_get_platdata(&pdev->dev);
	ret = kernel_connect(sample->qmi.sock, (काष्ठा sockaddr *)sq,
			     माप(*sq), 0);
	अगर (ret < 0) अणु
		pr_err("failed to connect to remote service port\n");
		जाओ err_release_qmi_handle;
	पूर्ण

	snम_लिखो(path, माप(path), "%d:%d", sq->sq_node, sq->sq_port);

	sample->de_dir = debugfs_create_dir(path, qmi_debug_dir);
	अगर (IS_ERR(sample->de_dir)) अणु
		ret = PTR_ERR(sample->de_dir);
		जाओ err_release_qmi_handle;
	पूर्ण

	sample->de_data = debugfs_create_file("data", 0600, sample->de_dir,
					      sample, &data_fops);
	अगर (IS_ERR(sample->de_data)) अणु
		ret = PTR_ERR(sample->de_data);
		जाओ err_हटाओ_de_dir;
	पूर्ण

	sample->de_ping = debugfs_create_file("ping", 0600, sample->de_dir,
					      sample, &ping_fops);
	अगर (IS_ERR(sample->de_ping)) अणु
		ret = PTR_ERR(sample->de_ping);
		जाओ err_हटाओ_de_data;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sample);

	वापस 0;

err_हटाओ_de_data:
	debugfs_हटाओ(sample->de_data);
err_हटाओ_de_dir:
	debugfs_हटाओ(sample->de_dir);
err_release_qmi_handle:
	qmi_handle_release(&sample->qmi);

	वापस ret;
पूर्ण

अटल पूर्णांक qmi_sample_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qmi_sample *sample = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ(sample->de_ping);
	debugfs_हटाओ(sample->de_data);
	debugfs_हटाओ(sample->de_dir);

	qmi_handle_release(&sample->qmi);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qmi_sample_driver = अणु
	.probe = qmi_sample_probe,
	.हटाओ = qmi_sample_हटाओ,
	.driver = अणु
		.name = "qmi_sample_client",
	पूर्ण,
पूर्ण;

अटल पूर्णांक qmi_sample_new_server(काष्ठा qmi_handle *qmi,
				 काष्ठा qmi_service *service)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा sockaddr_qrtr sq = अणु AF_QIPCRTR, service->node, service->port पूर्ण;
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc("qmi_sample_client", PLATFORM_DEVID_AUTO);
	अगर (!pdev)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(pdev, &sq, माप(sq));
	अगर (ret)
		जाओ err_put_device;

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		जाओ err_put_device;

	service->priv = pdev;

	वापस 0;

err_put_device:
	platक्रमm_device_put(pdev);

	वापस ret;
पूर्ण

अटल व्योम qmi_sample_del_server(काष्ठा qmi_handle *qmi,
				  काष्ठा qmi_service *service)
अणु
	काष्ठा platक्रमm_device *pdev = service->priv;

	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

अटल काष्ठा qmi_handle lookup_client;

अटल स्थिर काष्ठा qmi_ops lookup_ops = अणु
	.new_server = qmi_sample_new_server,
	.del_server = qmi_sample_del_server,
पूर्ण;

अटल पूर्णांक qmi_sample_init(व्योम)
अणु
	पूर्णांक ret;

	qmi_debug_dir = debugfs_create_dir("qmi_sample", शून्य);
	अगर (IS_ERR(qmi_debug_dir)) अणु
		pr_err("failed to create qmi_sample dir\n");
		वापस PTR_ERR(qmi_debug_dir);
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&qmi_sample_driver);
	अगर (ret)
		जाओ err_हटाओ_debug_dir;

	ret = qmi_handle_init(&lookup_client, 0, &lookup_ops, शून्य);
	अगर (ret < 0)
		जाओ err_unरेजिस्टर_driver;

	qmi_add_lookup(&lookup_client, 15, 0, 0);

	वापस 0;

err_unरेजिस्टर_driver:
	platक्रमm_driver_unरेजिस्टर(&qmi_sample_driver);
err_हटाओ_debug_dir:
	debugfs_हटाओ(qmi_debug_dir);

	वापस ret;
पूर्ण

अटल व्योम qmi_sample_निकास(व्योम)
अणु
	qmi_handle_release(&lookup_client);

	platक्रमm_driver_unरेजिस्टर(&qmi_sample_driver);

	debugfs_हटाओ(qmi_debug_dir);
पूर्ण

module_init(qmi_sample_init);
module_निकास(qmi_sample_निकास);

MODULE_DESCRIPTION("Sample QMI client driver");
MODULE_LICENSE("GPL v2");
