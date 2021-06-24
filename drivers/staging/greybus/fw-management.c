<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Firmware Management Protocol Driver.
 *
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */

#समावेश <linux/cdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/firmware.h>
#समावेश <linux/fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/greybus.h>

#समावेश "firmware.h"
#समावेश "greybus_firmware.h"

#घोषणा FW_MGMT_TIMEOUT_MS		1000

काष्ठा fw_mgmt अणु
	काष्ठा device		*parent;
	काष्ठा gb_connection	*connection;
	काष्ठा kref		kref;
	काष्ठा list_head	node;

	/* Common id-map क्रम पूर्णांकerface and backend firmware requests */
	काष्ठा ida		id_map;
	काष्ठा mutex		mutex;
	काष्ठा completion	completion;
	काष्ठा cdev		cdev;
	काष्ठा device		*class_device;
	dev_t			dev_num;
	अचिन्हित पूर्णांक		समयout_jअगरfies;
	bool			disabled; /* connection getting disabled */

	/* Interface Firmware specअगरic fields */
	bool			mode_चयन_started;
	bool			पूर्णांकf_fw_loaded;
	u8			पूर्णांकf_fw_request_id;
	u8			पूर्णांकf_fw_status;
	u16			पूर्णांकf_fw_major;
	u16			पूर्णांकf_fw_minor;

	/* Backend Firmware specअगरic fields */
	u8			backend_fw_request_id;
	u8			backend_fw_status;
पूर्ण;

/*
 * Number of minor devices this driver supports.
 * There will be exactly one required per Interface.
 */
#घोषणा NUM_MINORS		U8_MAX

अटल काष्ठा class *fw_mgmt_class;
अटल dev_t fw_mgmt_dev_num;
अटल DEFINE_IDA(fw_mgmt_minors_map);
अटल LIST_HEAD(fw_mgmt_list);
अटल DEFINE_MUTEX(list_mutex);

अटल व्योम fw_mgmt_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा fw_mgmt *fw_mgmt = container_of(kref, काष्ठा fw_mgmt, kref);

	ida_destroy(&fw_mgmt->id_map);
	kमुक्त(fw_mgmt);
पूर्ण

/*
 * All users of fw_mgmt take a reference (from within list_mutex lock), beक्रमe
 * they get a poपूर्णांकer to play with. And the काष्ठाure will be मुक्तd only after
 * the last user has put the reference to it.
 */
अटल व्योम put_fw_mgmt(काष्ठा fw_mgmt *fw_mgmt)
अणु
	kref_put(&fw_mgmt->kref, fw_mgmt_kref_release);
पूर्ण

/* Caller must call put_fw_mgmt() after using काष्ठा fw_mgmt */
अटल काष्ठा fw_mgmt *get_fw_mgmt(काष्ठा cdev *cdev)
अणु
	काष्ठा fw_mgmt *fw_mgmt;

	mutex_lock(&list_mutex);

	list_क्रम_each_entry(fw_mgmt, &fw_mgmt_list, node) अणु
		अगर (&fw_mgmt->cdev == cdev) अणु
			kref_get(&fw_mgmt->kref);
			जाओ unlock;
		पूर्ण
	पूर्ण

	fw_mgmt = शून्य;

unlock:
	mutex_unlock(&list_mutex);

	वापस fw_mgmt;
पूर्ण

अटल पूर्णांक fw_mgmt_पूर्णांकerface_fw_version_operation(काष्ठा fw_mgmt *fw_mgmt,
		काष्ठा fw_mgmt_ioc_get_पूर्णांकf_version *fw_info)
अणु
	काष्ठा gb_connection *connection = fw_mgmt->connection;
	काष्ठा gb_fw_mgmt_पूर्णांकerface_fw_version_response response;
	पूर्णांक ret;

	ret = gb_operation_sync(connection,
				GB_FW_MGMT_TYPE_INTERFACE_FW_VERSION, शून्य, 0,
				&response, माप(response));
	अगर (ret) अणु
		dev_err(fw_mgmt->parent,
			"failed to get interface firmware version (%d)\n", ret);
		वापस ret;
	पूर्ण

	fw_info->major = le16_to_cpu(response.major);
	fw_info->minor = le16_to_cpu(response.minor);

	म_नकलन(fw_info->firmware_tag, response.firmware_tag,
		GB_FIRMWARE_TAG_MAX_SIZE);

	/*
	 * The firmware-tag should be शून्य terminated, otherwise throw error but
	 * करोn't fail.
	 */
	अगर (fw_info->firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE - 1] != '\0') अणु
		dev_err(fw_mgmt->parent,
			"fw-version: firmware-tag is not NULL terminated\n");
		fw_info->firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE - 1] = '\0';
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fw_mgmt_load_and_validate_operation(काष्ठा fw_mgmt *fw_mgmt,
					       u8 load_method, स्थिर अक्षर *tag)
अणु
	काष्ठा gb_fw_mgmt_load_and_validate_fw_request request;
	पूर्णांक ret;

	अगर (load_method != GB_FW_LOAD_METHOD_UNIPRO &&
	    load_method != GB_FW_LOAD_METHOD_INTERNAL) अणु
		dev_err(fw_mgmt->parent,
			"invalid load-method (%d)\n", load_method);
		वापस -EINVAL;
	पूर्ण

	request.load_method = load_method;
	म_नकलन(request.firmware_tag, tag, GB_FIRMWARE_TAG_MAX_SIZE);

	/*
	 * The firmware-tag should be शून्य terminated, otherwise throw error and
	 * fail.
	 */
	अगर (request.firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE - 1] != '\0') अणु
		dev_err(fw_mgmt->parent, "load-and-validate: firmware-tag is not NULL terminated\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate ids from 1 to 255 (u8-max), 0 is an invalid id */
	ret = ida_simple_get(&fw_mgmt->id_map, 1, 256, GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(fw_mgmt->parent, "failed to allocate request id (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	fw_mgmt->पूर्णांकf_fw_request_id = ret;
	fw_mgmt->पूर्णांकf_fw_loaded = false;
	request.request_id = ret;

	ret = gb_operation_sync(fw_mgmt->connection,
				GB_FW_MGMT_TYPE_LOAD_AND_VALIDATE_FW, &request,
				माप(request), शून्य, 0);
	अगर (ret) अणु
		ida_simple_हटाओ(&fw_mgmt->id_map,
				  fw_mgmt->पूर्णांकf_fw_request_id);
		fw_mgmt->पूर्णांकf_fw_request_id = 0;
		dev_err(fw_mgmt->parent,
			"load and validate firmware request failed (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fw_mgmt_पूर्णांकerface_fw_loaded_operation(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा fw_mgmt *fw_mgmt = gb_connection_get_data(connection);
	काष्ठा gb_fw_mgmt_loaded_fw_request *request;

	/* No pending load and validate request ? */
	अगर (!fw_mgmt->पूर्णांकf_fw_request_id) अणु
		dev_err(fw_mgmt->parent,
			"unexpected firmware loaded request received\n");
		वापस -ENODEV;
	पूर्ण

	अगर (op->request->payload_size != माप(*request)) अणु
		dev_err(fw_mgmt->parent, "illegal size of firmware loaded request (%zu != %zu)\n",
			op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;

	/* Invalid request-id ? */
	अगर (request->request_id != fw_mgmt->पूर्णांकf_fw_request_id) अणु
		dev_err(fw_mgmt->parent, "invalid request id for firmware loaded request (%02u != %02u)\n",
			fw_mgmt->पूर्णांकf_fw_request_id, request->request_id);
		वापस -ENODEV;
	पूर्ण

	ida_simple_हटाओ(&fw_mgmt->id_map, fw_mgmt->पूर्णांकf_fw_request_id);
	fw_mgmt->पूर्णांकf_fw_request_id = 0;
	fw_mgmt->पूर्णांकf_fw_status = request->status;
	fw_mgmt->पूर्णांकf_fw_major = le16_to_cpu(request->major);
	fw_mgmt->पूर्णांकf_fw_minor = le16_to_cpu(request->minor);

	अगर (fw_mgmt->पूर्णांकf_fw_status == GB_FW_LOAD_STATUS_FAILED)
		dev_err(fw_mgmt->parent,
			"failed to load interface firmware, status:%02x\n",
			fw_mgmt->पूर्णांकf_fw_status);
	अन्यथा अगर (fw_mgmt->पूर्णांकf_fw_status == GB_FW_LOAD_STATUS_VALIDATION_FAILED)
		dev_err(fw_mgmt->parent,
			"failed to validate interface firmware, status:%02x\n",
			fw_mgmt->पूर्णांकf_fw_status);
	अन्यथा
		fw_mgmt->पूर्णांकf_fw_loaded = true;

	complete(&fw_mgmt->completion);

	वापस 0;
पूर्ण

अटल पूर्णांक fw_mgmt_backend_fw_version_operation(काष्ठा fw_mgmt *fw_mgmt,
		काष्ठा fw_mgmt_ioc_get_backend_version *fw_info)
अणु
	काष्ठा gb_connection *connection = fw_mgmt->connection;
	काष्ठा gb_fw_mgmt_backend_fw_version_request request;
	काष्ठा gb_fw_mgmt_backend_fw_version_response response;
	पूर्णांक ret;

	म_नकलन(request.firmware_tag, fw_info->firmware_tag,
		GB_FIRMWARE_TAG_MAX_SIZE);

	/*
	 * The firmware-tag should be शून्य terminated, otherwise throw error and
	 * fail.
	 */
	अगर (request.firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE - 1] != '\0') अणु
		dev_err(fw_mgmt->parent, "backend-version: firmware-tag is not NULL terminated\n");
		वापस -EINVAL;
	पूर्ण

	ret = gb_operation_sync(connection,
				GB_FW_MGMT_TYPE_BACKEND_FW_VERSION, &request,
				माप(request), &response, माप(response));
	अगर (ret) अणु
		dev_err(fw_mgmt->parent, "failed to get version of %s backend firmware (%d)\n",
			fw_info->firmware_tag, ret);
		वापस ret;
	पूर्ण

	fw_info->status = response.status;

	/* Reset version as that should be non-zero only क्रम success हाल */
	fw_info->major = 0;
	fw_info->minor = 0;

	चयन (fw_info->status) अणु
	हाल GB_FW_BACKEND_VERSION_STATUS_SUCCESS:
		fw_info->major = le16_to_cpu(response.major);
		fw_info->minor = le16_to_cpu(response.minor);
		अवरोध;
	हाल GB_FW_BACKEND_VERSION_STATUS_NOT_AVAILABLE:
	हाल GB_FW_BACKEND_VERSION_STATUS_RETRY:
		अवरोध;
	हाल GB_FW_BACKEND_VERSION_STATUS_NOT_SUPPORTED:
		dev_err(fw_mgmt->parent,
			"Firmware with tag %s is not supported by Interface\n",
			fw_info->firmware_tag);
		अवरोध;
	शेष:
		dev_err(fw_mgmt->parent, "Invalid status received: %u\n",
			fw_info->status);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fw_mgmt_backend_fw_update_operation(काष्ठा fw_mgmt *fw_mgmt,
					       अक्षर *tag)
अणु
	काष्ठा gb_fw_mgmt_backend_fw_update_request request;
	पूर्णांक ret;

	म_नकलन(request.firmware_tag, tag, GB_FIRMWARE_TAG_MAX_SIZE);

	/*
	 * The firmware-tag should be शून्य terminated, otherwise throw error and
	 * fail.
	 */
	अगर (request.firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE - 1] != '\0') अणु
		dev_err(fw_mgmt->parent, "backend-update: firmware-tag is not NULL terminated\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate ids from 1 to 255 (u8-max), 0 is an invalid id */
	ret = ida_simple_get(&fw_mgmt->id_map, 1, 256, GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(fw_mgmt->parent, "failed to allocate request id (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	fw_mgmt->backend_fw_request_id = ret;
	request.request_id = ret;

	ret = gb_operation_sync(fw_mgmt->connection,
				GB_FW_MGMT_TYPE_BACKEND_FW_UPDATE, &request,
				माप(request), शून्य, 0);
	अगर (ret) अणु
		ida_simple_हटाओ(&fw_mgmt->id_map,
				  fw_mgmt->backend_fw_request_id);
		fw_mgmt->backend_fw_request_id = 0;
		dev_err(fw_mgmt->parent,
			"backend %s firmware update request failed (%d)\n", tag,
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fw_mgmt_backend_fw_updated_operation(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा fw_mgmt *fw_mgmt = gb_connection_get_data(connection);
	काष्ठा gb_fw_mgmt_backend_fw_updated_request *request;

	/* No pending load and validate request ? */
	अगर (!fw_mgmt->backend_fw_request_id) अणु
		dev_err(fw_mgmt->parent, "unexpected backend firmware updated request received\n");
		वापस -ENODEV;
	पूर्ण

	अगर (op->request->payload_size != माप(*request)) अणु
		dev_err(fw_mgmt->parent, "illegal size of backend firmware updated request (%zu != %zu)\n",
			op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;

	/* Invalid request-id ? */
	अगर (request->request_id != fw_mgmt->backend_fw_request_id) अणु
		dev_err(fw_mgmt->parent, "invalid request id for backend firmware updated request (%02u != %02u)\n",
			fw_mgmt->backend_fw_request_id, request->request_id);
		वापस -ENODEV;
	पूर्ण

	ida_simple_हटाओ(&fw_mgmt->id_map, fw_mgmt->backend_fw_request_id);
	fw_mgmt->backend_fw_request_id = 0;
	fw_mgmt->backend_fw_status = request->status;

	अगर ((fw_mgmt->backend_fw_status != GB_FW_BACKEND_FW_STATUS_SUCCESS) &&
	    (fw_mgmt->backend_fw_status != GB_FW_BACKEND_FW_STATUS_RETRY))
		dev_err(fw_mgmt->parent,
			"failed to load backend firmware: %02x\n",
			fw_mgmt->backend_fw_status);

	complete(&fw_mgmt->completion);

	वापस 0;
पूर्ण

/* Char device fops */

अटल पूर्णांक fw_mgmt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fw_mgmt *fw_mgmt = get_fw_mgmt(inode->i_cdev);

	/* fw_mgmt काष्ठाure can't get मुक्तd until file descriptor is बंदd */
	अगर (fw_mgmt) अणु
		file->निजी_data = fw_mgmt;
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक fw_mgmt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fw_mgmt *fw_mgmt = file->निजी_data;

	put_fw_mgmt(fw_mgmt);
	वापस 0;
पूर्ण

अटल पूर्णांक fw_mgmt_ioctl(काष्ठा fw_mgmt *fw_mgmt, अचिन्हित पूर्णांक cmd,
			 व्योम __user *buf)
अणु
	काष्ठा fw_mgmt_ioc_get_पूर्णांकf_version पूर्णांकf_fw_info;
	काष्ठा fw_mgmt_ioc_get_backend_version backend_fw_info;
	काष्ठा fw_mgmt_ioc_पूर्णांकf_load_and_validate पूर्णांकf_load;
	काष्ठा fw_mgmt_ioc_backend_fw_update backend_update;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक ret;

	/* Reject any operations after mode-चयन has started */
	अगर (fw_mgmt->mode_चयन_started)
		वापस -EBUSY;

	चयन (cmd) अणु
	हाल FW_MGMT_IOC_GET_INTF_FW:
		ret = fw_mgmt_पूर्णांकerface_fw_version_operation(fw_mgmt,
							     &पूर्णांकf_fw_info);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user(buf, &पूर्णांकf_fw_info, माप(पूर्णांकf_fw_info)))
			वापस -EFAULT;

		वापस 0;
	हाल FW_MGMT_IOC_GET_BACKEND_FW:
		अगर (copy_from_user(&backend_fw_info, buf,
				   माप(backend_fw_info)))
			वापस -EFAULT;

		ret = fw_mgmt_backend_fw_version_operation(fw_mgmt,
							   &backend_fw_info);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user(buf, &backend_fw_info,
				 माप(backend_fw_info)))
			वापस -EFAULT;

		वापस 0;
	हाल FW_MGMT_IOC_INTF_LOAD_AND_VALIDATE:
		अगर (copy_from_user(&पूर्णांकf_load, buf, माप(पूर्णांकf_load)))
			वापस -EFAULT;

		ret = fw_mgmt_load_and_validate_operation(fw_mgmt,
				पूर्णांकf_load.load_method, पूर्णांकf_load.firmware_tag);
		अगर (ret)
			वापस ret;

		अगर (!रुको_क्रम_completion_समयout(&fw_mgmt->completion,
						 fw_mgmt->समयout_jअगरfies)) अणु
			dev_err(fw_mgmt->parent, "timed out waiting for firmware load and validation to finish\n");
			वापस -ETIMEDOUT;
		पूर्ण

		पूर्णांकf_load.status = fw_mgmt->पूर्णांकf_fw_status;
		पूर्णांकf_load.major = fw_mgmt->पूर्णांकf_fw_major;
		पूर्णांकf_load.minor = fw_mgmt->पूर्णांकf_fw_minor;

		अगर (copy_to_user(buf, &पूर्णांकf_load, माप(पूर्णांकf_load)))
			वापस -EFAULT;

		वापस 0;
	हाल FW_MGMT_IOC_INTF_BACKEND_FW_UPDATE:
		अगर (copy_from_user(&backend_update, buf,
				   माप(backend_update)))
			वापस -EFAULT;

		ret = fw_mgmt_backend_fw_update_operation(fw_mgmt,
				backend_update.firmware_tag);
		अगर (ret)
			वापस ret;

		अगर (!रुको_क्रम_completion_समयout(&fw_mgmt->completion,
						 fw_mgmt->समयout_jअगरfies)) अणु
			dev_err(fw_mgmt->parent, "timed out waiting for backend firmware update to finish\n");
			वापस -ETIMEDOUT;
		पूर्ण

		backend_update.status = fw_mgmt->backend_fw_status;

		अगर (copy_to_user(buf, &backend_update, माप(backend_update)))
			वापस -EFAULT;

		वापस 0;
	हाल FW_MGMT_IOC_SET_TIMEOUT_MS:
		अगर (get_user(समयout, (अचिन्हित पूर्णांक __user *)buf))
			वापस -EFAULT;

		अगर (!समयout) अणु
			dev_err(fw_mgmt->parent, "timeout can't be zero\n");
			वापस -EINVAL;
		पूर्ण

		fw_mgmt->समयout_jअगरfies = msecs_to_jअगरfies(समयout);

		वापस 0;
	हाल FW_MGMT_IOC_MODE_SWITCH:
		अगर (!fw_mgmt->पूर्णांकf_fw_loaded) अणु
			dev_err(fw_mgmt->parent,
				"Firmware not loaded for mode-switch\n");
			वापस -EPERM;
		पूर्ण

		/*
		 * Disallow new ioctls as the fw-core bundle driver is going to
		 * get disconnected soon and the अक्षरacter device will get
		 * हटाओd.
		 */
		fw_mgmt->mode_चयन_started = true;

		ret = gb_पूर्णांकerface_request_mode_चयन(fw_mgmt->connection->पूर्णांकf);
		अगर (ret) अणु
			dev_err(fw_mgmt->parent, "Mode-switch failed: %d\n",
				ret);
			fw_mgmt->mode_चयन_started = false;
			वापस ret;
		पूर्ण

		वापस 0;
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल दीर्घ fw_mgmt_ioctl_unlocked(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा fw_mgmt *fw_mgmt = file->निजी_data;
	काष्ठा gb_bundle *bundle = fw_mgmt->connection->bundle;
	पूर्णांक ret = -ENODEV;

	/*
	 * Serialize ioctls.
	 *
	 * We करोn't want the user to करो few operations in parallel. For example,
	 * updating Interface firmware in parallel क्रम the same Interface. There
	 * is no need to करो things in parallel क्रम speed and we can aव्योम having
	 * complicated code क्रम now.
	 *
	 * This is also used to protect ->disabled, which is used to check अगर
	 * the connection is getting disconnected, so that we करोn't start any
	 * new operations.
	 */
	mutex_lock(&fw_mgmt->mutex);
	अगर (!fw_mgmt->disabled) अणु
		ret = gb_pm_runसमय_get_sync(bundle);
		अगर (!ret) अणु
			ret = fw_mgmt_ioctl(fw_mgmt, cmd, (व्योम __user *)arg);
			gb_pm_runसमय_put_स्वतःsuspend(bundle);
		पूर्ण
	पूर्ण
	mutex_unlock(&fw_mgmt->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fw_mgmt_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fw_mgmt_खोलो,
	.release	= fw_mgmt_release,
	.unlocked_ioctl	= fw_mgmt_ioctl_unlocked,
पूर्ण;

पूर्णांक gb_fw_mgmt_request_handler(काष्ठा gb_operation *op)
अणु
	u8 type = op->type;

	चयन (type) अणु
	हाल GB_FW_MGMT_TYPE_LOADED_FW:
		वापस fw_mgmt_पूर्णांकerface_fw_loaded_operation(op);
	हाल GB_FW_MGMT_TYPE_BACKEND_FW_UPDATED:
		वापस fw_mgmt_backend_fw_updated_operation(op);
	शेष:
		dev_err(&op->connection->bundle->dev,
			"unsupported request: %u\n", type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक gb_fw_mgmt_connection_init(काष्ठा gb_connection *connection)
अणु
	काष्ठा fw_mgmt *fw_mgmt;
	पूर्णांक ret, minor;

	अगर (!connection)
		वापस 0;

	fw_mgmt = kzalloc(माप(*fw_mgmt), GFP_KERNEL);
	अगर (!fw_mgmt)
		वापस -ENOMEM;

	fw_mgmt->parent = &connection->bundle->dev;
	fw_mgmt->समयout_jअगरfies = msecs_to_jअगरfies(FW_MGMT_TIMEOUT_MS);
	fw_mgmt->connection = connection;

	gb_connection_set_data(connection, fw_mgmt);
	init_completion(&fw_mgmt->completion);
	ida_init(&fw_mgmt->id_map);
	mutex_init(&fw_mgmt->mutex);
	kref_init(&fw_mgmt->kref);

	mutex_lock(&list_mutex);
	list_add(&fw_mgmt->node, &fw_mgmt_list);
	mutex_unlock(&list_mutex);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ err_list_del;

	minor = ida_simple_get(&fw_mgmt_minors_map, 0, NUM_MINORS, GFP_KERNEL);
	अगर (minor < 0) अणु
		ret = minor;
		जाओ err_connection_disable;
	पूर्ण

	/* Add a अक्षर device to allow userspace to पूर्णांकeract with fw-mgmt */
	fw_mgmt->dev_num = MKDEV(MAJOR(fw_mgmt_dev_num), minor);
	cdev_init(&fw_mgmt->cdev, &fw_mgmt_fops);

	ret = cdev_add(&fw_mgmt->cdev, fw_mgmt->dev_num, 1);
	अगर (ret)
		जाओ err_हटाओ_ida;

	/* Add a soft link to the previously added अक्षर-dev within the bundle */
	fw_mgmt->class_device = device_create(fw_mgmt_class, fw_mgmt->parent,
					      fw_mgmt->dev_num, शून्य,
					      "gb-fw-mgmt-%d", minor);
	अगर (IS_ERR(fw_mgmt->class_device)) अणु
		ret = PTR_ERR(fw_mgmt->class_device);
		जाओ err_del_cdev;
	पूर्ण

	वापस 0;

err_del_cdev:
	cdev_del(&fw_mgmt->cdev);
err_हटाओ_ida:
	ida_simple_हटाओ(&fw_mgmt_minors_map, minor);
err_connection_disable:
	gb_connection_disable(connection);
err_list_del:
	mutex_lock(&list_mutex);
	list_del(&fw_mgmt->node);
	mutex_unlock(&list_mutex);

	put_fw_mgmt(fw_mgmt);

	वापस ret;
पूर्ण

व्योम gb_fw_mgmt_connection_निकास(काष्ठा gb_connection *connection)
अणु
	काष्ठा fw_mgmt *fw_mgmt;

	अगर (!connection)
		वापस;

	fw_mgmt = gb_connection_get_data(connection);

	device_destroy(fw_mgmt_class, fw_mgmt->dev_num);
	cdev_del(&fw_mgmt->cdev);
	ida_simple_हटाओ(&fw_mgmt_minors_map, MINOR(fw_mgmt->dev_num));

	/*
	 * Disallow any new ioctl operations on the अक्षर device and रुको क्रम
	 * existing ones to finish.
	 */
	mutex_lock(&fw_mgmt->mutex);
	fw_mgmt->disabled = true;
	mutex_unlock(&fw_mgmt->mutex);

	/* All pending greybus operations should have finished by now */
	gb_connection_disable(fw_mgmt->connection);

	/* Disallow new users to get access to the fw_mgmt काष्ठाure */
	mutex_lock(&list_mutex);
	list_del(&fw_mgmt->node);
	mutex_unlock(&list_mutex);

	/*
	 * All current users of fw_mgmt would have taken a reference to it by
	 * now, we can drop our reference and रुको the last user will get
	 * fw_mgmt मुक्तd.
	 */
	put_fw_mgmt(fw_mgmt);
पूर्ण

पूर्णांक fw_mgmt_init(व्योम)
अणु
	पूर्णांक ret;

	fw_mgmt_class = class_create(THIS_MODULE, "gb_fw_mgmt");
	अगर (IS_ERR(fw_mgmt_class))
		वापस PTR_ERR(fw_mgmt_class);

	ret = alloc_chrdev_region(&fw_mgmt_dev_num, 0, NUM_MINORS,
				  "gb_fw_mgmt");
	अगर (ret)
		जाओ err_हटाओ_class;

	वापस 0;

err_हटाओ_class:
	class_destroy(fw_mgmt_class);
	वापस ret;
पूर्ण

व्योम fw_mgmt_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(fw_mgmt_dev_num, NUM_MINORS);
	class_destroy(fw_mgmt_class);
	ida_destroy(&fw_mgmt_minors_map);
पूर्ण
