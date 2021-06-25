<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Firmware Download Protocol Driver.
 *
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */

#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/greybus.h>
#समावेश "firmware.h"

/* Estimated minimum buffer size, actual size can be smaller than this */
#घोषणा MIN_FETCH_SIZE		512
/* Timeout, in jअगरfies, within which fetch or release firmware must be called */
#घोषणा NEXT_REQ_TIMEOUT_J	msecs_to_jअगरfies(1000)

काष्ठा fw_request अणु
	u8			firmware_id;
	bool			disabled;
	bool			समयकरोut;
	अक्षर			name[FW_NAME_SIZE];
	स्थिर काष्ठा firmware	*fw;
	काष्ठा list_head	node;

	काष्ठा delayed_work	dwork;
	/* Timeout, in jअगरfies, within which the firmware shall करोwnload */
	अचिन्हित दीर्घ		release_समयout_j;
	काष्ठा kref		kref;
	काष्ठा fw_करोwnload	*fw_करोwnload;
पूर्ण;

काष्ठा fw_करोwnload अणु
	काष्ठा device		*parent;
	काष्ठा gb_connection	*connection;
	काष्ठा list_head	fw_requests;
	काष्ठा ida		id_map;
	काष्ठा mutex		mutex;
पूर्ण;

अटल व्योम fw_req_release(काष्ठा kref *kref)
अणु
	काष्ठा fw_request *fw_req = container_of(kref, काष्ठा fw_request, kref);

	dev_dbg(fw_req->fw_करोwnload->parent, "firmware %s released\n",
		fw_req->name);

	release_firmware(fw_req->fw);

	/*
	 * The request समयd out and the module may send a fetch-fw or
	 * release-fw request later. Lets block the id we allocated क्रम this
	 * request, so that the AP करोesn't refer to a later fw-request (with
	 * same firmware_id) क्रम the old समयकरोut fw-request.
	 *
	 * NOTE:
	 *
	 * This also means that after 255 समयouts we will fail to service new
	 * firmware करोwnloads. But what अन्यथा can we करो in that हाल anyway? Lets
	 * just hope that it never happens.
	 */
	अगर (!fw_req->समयकरोut)
		ida_simple_हटाओ(&fw_req->fw_करोwnload->id_map,
				  fw_req->firmware_id);

	kमुक्त(fw_req);
पूर्ण

/*
 * Incoming requests are serialized क्रम a connection, and the only race possible
 * is between the समयout handler मुक्तing this and an incoming request.
 *
 * The operations on the fw-request list are रक्षित by the mutex and
 * get_fw_req() increments the reference count beक्रमe वापसing a fw_req poपूर्णांकer
 * to the users.
 *
 * मुक्त_firmware() also takes the mutex जबतक removing an entry from the list,
 * it guarantees that every user of fw_req has taken a kref-reference by now and
 * we wouldn't have any new users.
 *
 * Once the last user drops the reference, the fw_req काष्ठाure is मुक्तd.
 */
अटल व्योम put_fw_req(काष्ठा fw_request *fw_req)
अणु
	kref_put(&fw_req->kref, fw_req_release);
पूर्ण

/* Caller must call put_fw_req() after using काष्ठा fw_request */
अटल काष्ठा fw_request *get_fw_req(काष्ठा fw_करोwnload *fw_करोwnload,
				     u8 firmware_id)
अणु
	काष्ठा fw_request *fw_req;

	mutex_lock(&fw_करोwnload->mutex);

	list_क्रम_each_entry(fw_req, &fw_करोwnload->fw_requests, node) अणु
		अगर (fw_req->firmware_id == firmware_id) अणु
			kref_get(&fw_req->kref);
			जाओ unlock;
		पूर्ण
	पूर्ण

	fw_req = शून्य;

unlock:
	mutex_unlock(&fw_करोwnload->mutex);

	वापस fw_req;
पूर्ण

अटल व्योम मुक्त_firmware(काष्ठा fw_करोwnload *fw_करोwnload,
			  काष्ठा fw_request *fw_req)
अणु
	/* Alपढ़ोy disabled from समयout handlers */
	अगर (fw_req->disabled)
		वापस;

	mutex_lock(&fw_करोwnload->mutex);
	list_del(&fw_req->node);
	mutex_unlock(&fw_करोwnload->mutex);

	fw_req->disabled = true;
	put_fw_req(fw_req);
पूर्ण

अटल व्योम fw_request_समयकरोut(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा fw_request *fw_req = container_of(dwork,
						 काष्ठा fw_request, dwork);
	काष्ठा fw_करोwnload *fw_करोwnload = fw_req->fw_करोwnload;

	dev_err(fw_करोwnload->parent,
		"Timed out waiting for fetch / release firmware requests: %u\n",
		fw_req->firmware_id);

	fw_req->समयकरोut = true;
	मुक्त_firmware(fw_करोwnload, fw_req);
पूर्ण

अटल पूर्णांक exceeds_release_समयout(काष्ठा fw_request *fw_req)
अणु
	काष्ठा fw_करोwnload *fw_करोwnload = fw_req->fw_करोwnload;

	अगर (समय_beक्रमe(jअगरfies, fw_req->release_समयout_j))
		वापस 0;

	dev_err(fw_करोwnload->parent,
		"Firmware download didn't finish in time, abort: %d\n",
		fw_req->firmware_id);

	fw_req->समयकरोut = true;
	मुक्त_firmware(fw_करोwnload, fw_req);

	वापस -ETIMEDOUT;
पूर्ण

/* This वापसs path of the firmware blob on the disk */
अटल काष्ठा fw_request *find_firmware(काष्ठा fw_करोwnload *fw_करोwnload,
					स्थिर अक्षर *tag)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = fw_करोwnload->connection->bundle->पूर्णांकf;
	काष्ठा fw_request *fw_req;
	पूर्णांक ret, req_count;

	fw_req = kzalloc(माप(*fw_req), GFP_KERNEL);
	अगर (!fw_req)
		वापस ERR_PTR(-ENOMEM);

	/* Allocate ids from 1 to 255 (u8-max), 0 is an invalid id */
	ret = ida_simple_get(&fw_करोwnload->id_map, 1, 256, GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(fw_करोwnload->parent,
			"failed to allocate firmware id (%d)\n", ret);
		जाओ err_मुक्त_req;
	पूर्ण
	fw_req->firmware_id = ret;

	snम_लिखो(fw_req->name, माप(fw_req->name),
		 FW_NAME_PREFIX "%08x_%08x_%08x_%08x_%s.tftf",
		 पूर्णांकf->ddbl1_manufacturer_id, पूर्णांकf->ddbl1_product_id,
		 पूर्णांकf->venकरोr_id, पूर्णांकf->product_id, tag);

	dev_info(fw_करोwnload->parent, "Requested firmware package '%s'\n",
		 fw_req->name);

	ret = request_firmware(&fw_req->fw, fw_req->name, fw_करोwnload->parent);
	अगर (ret) अणु
		dev_err(fw_करोwnload->parent,
			"firmware request failed for %s (%d)\n", fw_req->name,
			ret);
		जाओ err_मुक्त_id;
	पूर्ण

	fw_req->fw_करोwnload = fw_करोwnload;
	kref_init(&fw_req->kref);

	mutex_lock(&fw_करोwnload->mutex);
	list_add(&fw_req->node, &fw_करोwnload->fw_requests);
	mutex_unlock(&fw_करोwnload->mutex);

	/* Timeout, in jअगरfies, within which firmware should get loaded */
	req_count = DIV_ROUND_UP(fw_req->fw->size, MIN_FETCH_SIZE);
	fw_req->release_समयout_j = jअगरfies + req_count * NEXT_REQ_TIMEOUT_J;

	INIT_DELAYED_WORK(&fw_req->dwork, fw_request_समयकरोut);
	schedule_delayed_work(&fw_req->dwork, NEXT_REQ_TIMEOUT_J);

	वापस fw_req;

err_मुक्त_id:
	ida_simple_हटाओ(&fw_करोwnload->id_map, fw_req->firmware_id);
err_मुक्त_req:
	kमुक्त(fw_req);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक fw_करोwnload_find_firmware(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा fw_करोwnload *fw_करोwnload = gb_connection_get_data(connection);
	काष्ठा gb_fw_करोwnload_find_firmware_request *request;
	काष्ठा gb_fw_करोwnload_find_firmware_response *response;
	काष्ठा fw_request *fw_req;
	स्थिर अक्षर *tag;

	अगर (op->request->payload_size != माप(*request)) अणु
		dev_err(fw_करोwnload->parent,
			"illegal size of find firmware request (%zu != %zu)\n",
			op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;
	tag = (स्थिर अक्षर *)request->firmware_tag;

	/* firmware_tag must be null-terminated */
	अगर (strnlen(tag, GB_FIRMWARE_TAG_MAX_SIZE) ==
	    GB_FIRMWARE_TAG_MAX_SIZE) अणु
		dev_err(fw_करोwnload->parent,
			"firmware-tag is not null-terminated\n");
		वापस -EINVAL;
	पूर्ण

	fw_req = find_firmware(fw_करोwnload, tag);
	अगर (IS_ERR(fw_req))
		वापस PTR_ERR(fw_req);

	अगर (!gb_operation_response_alloc(op, माप(*response), GFP_KERNEL)) अणु
		dev_err(fw_करोwnload->parent, "error allocating response\n");
		मुक्त_firmware(fw_करोwnload, fw_req);
		वापस -ENOMEM;
	पूर्ण

	response = op->response->payload;
	response->firmware_id = fw_req->firmware_id;
	response->size = cpu_to_le32(fw_req->fw->size);

	dev_dbg(fw_करोwnload->parent,
		"firmware size is %zu bytes\n", fw_req->fw->size);

	वापस 0;
पूर्ण

अटल पूर्णांक fw_करोwnload_fetch_firmware(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा fw_करोwnload *fw_करोwnload = gb_connection_get_data(connection);
	काष्ठा gb_fw_करोwnload_fetch_firmware_request *request;
	काष्ठा gb_fw_करोwnload_fetch_firmware_response *response;
	काष्ठा fw_request *fw_req;
	स्थिर काष्ठा firmware *fw;
	अचिन्हित पूर्णांक offset, size;
	u8 firmware_id;
	पूर्णांक ret = 0;

	अगर (op->request->payload_size != माप(*request)) अणु
		dev_err(fw_करोwnload->parent,
			"Illegal size of fetch firmware request (%zu %zu)\n",
			op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;
	offset = le32_to_cpu(request->offset);
	size = le32_to_cpu(request->size);
	firmware_id = request->firmware_id;

	fw_req = get_fw_req(fw_करोwnload, firmware_id);
	अगर (!fw_req) अणु
		dev_err(fw_करोwnload->parent,
			"firmware not available for id: %02u\n", firmware_id);
		वापस -EINVAL;
	पूर्ण

	/* Make sure work handler isn't running in parallel */
	cancel_delayed_work_sync(&fw_req->dwork);

	/* We समयd-out beक्रमe reaching here ? */
	अगर (fw_req->disabled) अणु
		ret = -ETIMEDOUT;
		जाओ put_fw;
	पूर्ण

	/*
	 * Firmware करोwnload must finish within a limited समय पूर्णांकerval. If it
	 * करोesn't, then we might have a buggy Module on the other side. Abort
	 * करोwnload.
	 */
	ret = exceeds_release_समयout(fw_req);
	अगर (ret)
		जाओ put_fw;

	fw = fw_req->fw;

	अगर (offset >= fw->size || size > fw->size - offset) अणु
		dev_err(fw_करोwnload->parent,
			"bad fetch firmware request (offs = %u, size = %u)\n",
			offset, size);
		ret = -EINVAL;
		जाओ put_fw;
	पूर्ण

	अगर (!gb_operation_response_alloc(op, माप(*response) + size,
					 GFP_KERNEL)) अणु
		dev_err(fw_करोwnload->parent,
			"error allocating fetch firmware response\n");
		ret = -ENOMEM;
		जाओ put_fw;
	पूर्ण

	response = op->response->payload;
	स_नकल(response->data, fw->data + offset, size);

	dev_dbg(fw_करोwnload->parent,
		"responding with firmware (offs = %u, size = %u)\n", offset,
		size);

	/* Refresh समयout */
	schedule_delayed_work(&fw_req->dwork, NEXT_REQ_TIMEOUT_J);

put_fw:
	put_fw_req(fw_req);

	वापस ret;
पूर्ण

अटल पूर्णांक fw_करोwnload_release_firmware(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा fw_करोwnload *fw_करोwnload = gb_connection_get_data(connection);
	काष्ठा gb_fw_करोwnload_release_firmware_request *request;
	काष्ठा fw_request *fw_req;
	u8 firmware_id;

	अगर (op->request->payload_size != माप(*request)) अणु
		dev_err(fw_करोwnload->parent,
			"Illegal size of release firmware request (%zu %zu)\n",
			op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;
	firmware_id = request->firmware_id;

	fw_req = get_fw_req(fw_करोwnload, firmware_id);
	अगर (!fw_req) अणु
		dev_err(fw_करोwnload->parent,
			"firmware not available for id: %02u\n", firmware_id);
		वापस -EINVAL;
	पूर्ण

	cancel_delayed_work_sync(&fw_req->dwork);

	मुक्त_firmware(fw_करोwnload, fw_req);
	put_fw_req(fw_req);

	dev_dbg(fw_करोwnload->parent, "release firmware\n");

	वापस 0;
पूर्ण

पूर्णांक gb_fw_करोwnload_request_handler(काष्ठा gb_operation *op)
अणु
	u8 type = op->type;

	चयन (type) अणु
	हाल GB_FW_DOWNLOAD_TYPE_FIND_FIRMWARE:
		वापस fw_करोwnload_find_firmware(op);
	हाल GB_FW_DOWNLOAD_TYPE_FETCH_FIRMWARE:
		वापस fw_करोwnload_fetch_firmware(op);
	हाल GB_FW_DOWNLOAD_TYPE_RELEASE_FIRMWARE:
		वापस fw_करोwnload_release_firmware(op);
	शेष:
		dev_err(&op->connection->bundle->dev,
			"unsupported request: %u\n", type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक gb_fw_करोwnload_connection_init(काष्ठा gb_connection *connection)
अणु
	काष्ठा fw_करोwnload *fw_करोwnload;
	पूर्णांक ret;

	अगर (!connection)
		वापस 0;

	fw_करोwnload = kzalloc(माप(*fw_करोwnload), GFP_KERNEL);
	अगर (!fw_करोwnload)
		वापस -ENOMEM;

	fw_करोwnload->parent = &connection->bundle->dev;
	INIT_LIST_HEAD(&fw_करोwnload->fw_requests);
	ida_init(&fw_करोwnload->id_map);
	gb_connection_set_data(connection, fw_करोwnload);
	fw_करोwnload->connection = connection;
	mutex_init(&fw_करोwnload->mutex);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ err_destroy_id_map;

	वापस 0;

err_destroy_id_map:
	ida_destroy(&fw_करोwnload->id_map);
	kमुक्त(fw_करोwnload);

	वापस ret;
पूर्ण

व्योम gb_fw_करोwnload_connection_निकास(काष्ठा gb_connection *connection)
अणु
	काष्ठा fw_करोwnload *fw_करोwnload;
	काष्ठा fw_request *fw_req, *पंचांगp;

	अगर (!connection)
		वापस;

	fw_करोwnload = gb_connection_get_data(connection);
	gb_connection_disable(fw_करोwnload->connection);

	/*
	 * Make sure we have a reference to the pending requests, beक्रमe they
	 * are मुक्तd from the समयout handler.
	 */
	mutex_lock(&fw_करोwnload->mutex);
	list_क्रम_each_entry(fw_req, &fw_करोwnload->fw_requests, node)
		kref_get(&fw_req->kref);
	mutex_unlock(&fw_करोwnload->mutex);

	/* Release pending firmware packages */
	list_क्रम_each_entry_safe(fw_req, पंचांगp, &fw_करोwnload->fw_requests, node) अणु
		cancel_delayed_work_sync(&fw_req->dwork);
		मुक्त_firmware(fw_करोwnload, fw_req);
		put_fw_req(fw_req);
	पूर्ण

	ida_destroy(&fw_करोwnload->id_map);
	kमुक्त(fw_करोwnload);
पूर्ण
