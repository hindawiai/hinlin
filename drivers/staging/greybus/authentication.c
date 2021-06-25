<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Component Authentication Protocol (CAP) Driver.
 *
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */

#समावेश <linux/greybus.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>

#समावेश "greybus_authentication.h"
#समावेश "firmware.h"

#घोषणा CAP_TIMEOUT_MS		1000

/*
 * Number of minor devices this driver supports.
 * There will be exactly one required per Interface.
 */
#घोषणा NUM_MINORS		U8_MAX

काष्ठा gb_cap अणु
	काष्ठा device		*parent;
	काष्ठा gb_connection	*connection;
	काष्ठा kref		kref;
	काष्ठा list_head	node;
	bool			disabled; /* connection getting disabled */

	काष्ठा mutex		mutex;
	काष्ठा cdev		cdev;
	काष्ठा device		*class_device;
	dev_t			dev_num;
पूर्ण;

अटल काष्ठा class *cap_class;
अटल dev_t cap_dev_num;
अटल DEFINE_IDA(cap_minors_map);
अटल LIST_HEAD(cap_list);
अटल DEFINE_MUTEX(list_mutex);

अटल व्योम cap_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा gb_cap *cap = container_of(kref, काष्ठा gb_cap, kref);

	kमुक्त(cap);
पूर्ण

/*
 * All users of cap take a reference (from within list_mutex lock), beक्रमe
 * they get a poपूर्णांकer to play with. And the काष्ठाure will be मुक्तd only after
 * the last user has put the reference to it.
 */
अटल व्योम put_cap(काष्ठा gb_cap *cap)
अणु
	kref_put(&cap->kref, cap_kref_release);
पूर्ण

/* Caller must call put_cap() after using काष्ठा gb_cap */
अटल काष्ठा gb_cap *get_cap(काष्ठा cdev *cdev)
अणु
	काष्ठा gb_cap *cap;

	mutex_lock(&list_mutex);

	list_क्रम_each_entry(cap, &cap_list, node) अणु
		अगर (&cap->cdev == cdev) अणु
			kref_get(&cap->kref);
			जाओ unlock;
		पूर्ण
	पूर्ण

	cap = शून्य;

unlock:
	mutex_unlock(&list_mutex);

	वापस cap;
पूर्ण

अटल पूर्णांक cap_get_endpoपूर्णांक_uid(काष्ठा gb_cap *cap, u8 *euid)
अणु
	काष्ठा gb_connection *connection = cap->connection;
	काष्ठा gb_cap_get_endpoपूर्णांक_uid_response response;
	पूर्णांक ret;

	ret = gb_operation_sync(connection, GB_CAP_TYPE_GET_ENDPOINT_UID, शून्य,
				0, &response, माप(response));
	अगर (ret) अणु
		dev_err(cap->parent, "failed to get endpoint uid (%d)\n", ret);
		वापस ret;
	पूर्ण

	स_नकल(euid, response.uid, माप(response.uid));

	वापस 0;
पूर्ण

अटल पूर्णांक cap_get_ims_certअगरicate(काष्ठा gb_cap *cap, u32 class, u32 id,
				   u8 *certअगरicate, u32 *size, u8 *result)
अणु
	काष्ठा gb_connection *connection = cap->connection;
	काष्ठा gb_cap_get_ims_certअगरicate_request *request;
	काष्ठा gb_cap_get_ims_certअगरicate_response *response;
	माप_प्रकार max_size = gb_operation_get_payload_size_max(connection);
	काष्ठा gb_operation *op;
	पूर्णांक ret;

	op = gb_operation_create_flags(connection,
				       GB_CAP_TYPE_GET_IMS_CERTIFICATE,
				       माप(*request), max_size,
				       GB_OPERATION_FLAG_SHORT_RESPONSE,
				       GFP_KERNEL);
	अगर (!op)
		वापस -ENOMEM;

	request = op->request->payload;
	request->certअगरicate_class = cpu_to_le32(class);
	request->certअगरicate_id = cpu_to_le32(id);

	ret = gb_operation_request_send_sync(op);
	अगर (ret) अणु
		dev_err(cap->parent, "failed to get certificate (%d)\n", ret);
		जाओ करोne;
	पूर्ण

	response = op->response->payload;
	*result = response->result_code;
	*size = op->response->payload_size - माप(*response);
	स_नकल(certअगरicate, response->certअगरicate, *size);

करोne:
	gb_operation_put(op);
	वापस ret;
पूर्ण

अटल पूर्णांक cap_authenticate(काष्ठा gb_cap *cap, u32 auth_type, u8 *uid,
			    u8 *challenge, u8 *result, u8 *auth_response,
			    u32 *signature_size, u8 *signature)
अणु
	काष्ठा gb_connection *connection = cap->connection;
	काष्ठा gb_cap_authenticate_request *request;
	काष्ठा gb_cap_authenticate_response *response;
	माप_प्रकार max_size = gb_operation_get_payload_size_max(connection);
	काष्ठा gb_operation *op;
	पूर्णांक ret;

	op = gb_operation_create_flags(connection, GB_CAP_TYPE_AUTHENTICATE,
				       माप(*request), max_size,
				       GB_OPERATION_FLAG_SHORT_RESPONSE,
				       GFP_KERNEL);
	अगर (!op)
		वापस -ENOMEM;

	request = op->request->payload;
	request->auth_type = cpu_to_le32(auth_type);
	स_नकल(request->uid, uid, माप(request->uid));
	स_नकल(request->challenge, challenge, माप(request->challenge));

	ret = gb_operation_request_send_sync(op);
	अगर (ret) अणु
		dev_err(cap->parent, "failed to authenticate (%d)\n", ret);
		जाओ करोne;
	पूर्ण

	response = op->response->payload;
	*result = response->result_code;
	*signature_size = op->response->payload_size - माप(*response);
	स_नकल(auth_response, response->response, माप(response->response));
	स_नकल(signature, response->signature, *signature_size);

करोne:
	gb_operation_put(op);
	वापस ret;
पूर्ण

/* Char device fops */

अटल पूर्णांक cap_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gb_cap *cap = get_cap(inode->i_cdev);

	/* cap काष्ठाure can't get मुक्तd until file descriptor is बंदd */
	अगर (cap) अणु
		file->निजी_data = cap;
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक cap_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gb_cap *cap = file->निजी_data;

	put_cap(cap);
	वापस 0;
पूर्ण

अटल पूर्णांक cap_ioctl(काष्ठा gb_cap *cap, अचिन्हित पूर्णांक cmd,
		     व्योम __user *buf)
अणु
	काष्ठा cap_ioc_get_endpoपूर्णांक_uid endpoपूर्णांक_uid;
	काष्ठा cap_ioc_get_ims_certअगरicate *ims_cert;
	काष्ठा cap_ioc_authenticate *authenticate;
	माप_प्रकार size;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल CAP_IOC_GET_ENDPOINT_UID:
		ret = cap_get_endpoपूर्णांक_uid(cap, endpoपूर्णांक_uid.uid);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user(buf, &endpoपूर्णांक_uid, माप(endpoपूर्णांक_uid)))
			वापस -EFAULT;

		वापस 0;
	हाल CAP_IOC_GET_IMS_CERTIFICATE:
		size = माप(*ims_cert);
		ims_cert = memdup_user(buf, size);
		अगर (IS_ERR(ims_cert))
			वापस PTR_ERR(ims_cert);

		ret = cap_get_ims_certअगरicate(cap, ims_cert->certअगरicate_class,
					      ims_cert->certअगरicate_id,
					      ims_cert->certअगरicate,
					      &ims_cert->cert_size,
					      &ims_cert->result_code);
		अगर (!ret && copy_to_user(buf, ims_cert, size))
			ret = -EFAULT;
		kमुक्त(ims_cert);

		वापस ret;
	हाल CAP_IOC_AUTHENTICATE:
		size = माप(*authenticate);
		authenticate = memdup_user(buf, size);
		अगर (IS_ERR(authenticate))
			वापस PTR_ERR(authenticate);

		ret = cap_authenticate(cap, authenticate->auth_type,
				       authenticate->uid,
				       authenticate->challenge,
				       &authenticate->result_code,
				       authenticate->response,
				       &authenticate->signature_size,
				       authenticate->signature);
		अगर (!ret && copy_to_user(buf, authenticate, size))
			ret = -EFAULT;
		kमुक्त(authenticate);

		वापस ret;
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल दीर्घ cap_ioctl_unlocked(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	काष्ठा gb_cap *cap = file->निजी_data;
	काष्ठा gb_bundle *bundle = cap->connection->bundle;
	पूर्णांक ret = -ENODEV;

	/*
	 * Serialize ioctls.
	 *
	 * We करोn't want the user to करो multiple authentication operations in
	 * parallel.
	 *
	 * This is also used to protect ->disabled, which is used to check अगर
	 * the connection is getting disconnected, so that we करोn't start any
	 * new operations.
	 */
	mutex_lock(&cap->mutex);
	अगर (!cap->disabled) अणु
		ret = gb_pm_runसमय_get_sync(bundle);
		अगर (!ret) अणु
			ret = cap_ioctl(cap, cmd, (व्योम __user *)arg);
			gb_pm_runसमय_put_स्वतःsuspend(bundle);
		पूर्ण
	पूर्ण
	mutex_unlock(&cap->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations cap_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= cap_खोलो,
	.release	= cap_release,
	.unlocked_ioctl	= cap_ioctl_unlocked,
पूर्ण;

पूर्णांक gb_cap_connection_init(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_cap *cap;
	पूर्णांक ret, minor;

	अगर (!connection)
		वापस 0;

	cap = kzalloc(माप(*cap), GFP_KERNEL);
	अगर (!cap)
		वापस -ENOMEM;

	cap->parent = &connection->bundle->dev;
	cap->connection = connection;
	mutex_init(&cap->mutex);
	gb_connection_set_data(connection, cap);
	kref_init(&cap->kref);

	mutex_lock(&list_mutex);
	list_add(&cap->node, &cap_list);
	mutex_unlock(&list_mutex);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ err_list_del;

	minor = ida_simple_get(&cap_minors_map, 0, NUM_MINORS, GFP_KERNEL);
	अगर (minor < 0) अणु
		ret = minor;
		जाओ err_connection_disable;
	पूर्ण

	/* Add a अक्षर device to allow userspace to पूर्णांकeract with cap */
	cap->dev_num = MKDEV(MAJOR(cap_dev_num), minor);
	cdev_init(&cap->cdev, &cap_fops);

	ret = cdev_add(&cap->cdev, cap->dev_num, 1);
	अगर (ret)
		जाओ err_हटाओ_ida;

	/* Add a soft link to the previously added अक्षर-dev within the bundle */
	cap->class_device = device_create(cap_class, cap->parent, cap->dev_num,
					  शून्य, "gb-authenticate-%d", minor);
	अगर (IS_ERR(cap->class_device)) अणु
		ret = PTR_ERR(cap->class_device);
		जाओ err_del_cdev;
	पूर्ण

	वापस 0;

err_del_cdev:
	cdev_del(&cap->cdev);
err_हटाओ_ida:
	ida_simple_हटाओ(&cap_minors_map, minor);
err_connection_disable:
	gb_connection_disable(connection);
err_list_del:
	mutex_lock(&list_mutex);
	list_del(&cap->node);
	mutex_unlock(&list_mutex);

	put_cap(cap);

	वापस ret;
पूर्ण

व्योम gb_cap_connection_निकास(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_cap *cap;

	अगर (!connection)
		वापस;

	cap = gb_connection_get_data(connection);

	device_destroy(cap_class, cap->dev_num);
	cdev_del(&cap->cdev);
	ida_simple_हटाओ(&cap_minors_map, MINOR(cap->dev_num));

	/*
	 * Disallow any new ioctl operations on the अक्षर device and रुको क्रम
	 * existing ones to finish.
	 */
	mutex_lock(&cap->mutex);
	cap->disabled = true;
	mutex_unlock(&cap->mutex);

	/* All pending greybus operations should have finished by now */
	gb_connection_disable(cap->connection);

	/* Disallow new users to get access to the cap काष्ठाure */
	mutex_lock(&list_mutex);
	list_del(&cap->node);
	mutex_unlock(&list_mutex);

	/*
	 * All current users of cap would have taken a reference to it by
	 * now, we can drop our reference and रुको the last user will get
	 * cap मुक्तd.
	 */
	put_cap(cap);
पूर्ण

पूर्णांक cap_init(व्योम)
अणु
	पूर्णांक ret;

	cap_class = class_create(THIS_MODULE, "gb_authenticate");
	अगर (IS_ERR(cap_class))
		वापस PTR_ERR(cap_class);

	ret = alloc_chrdev_region(&cap_dev_num, 0, NUM_MINORS,
				  "gb_authenticate");
	अगर (ret)
		जाओ err_हटाओ_class;

	वापस 0;

err_हटाओ_class:
	class_destroy(cap_class);
	वापस ret;
पूर्ण

व्योम cap_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(cap_dev_num, NUM_MINORS);
	class_destroy(cap_class);
	ida_destroy(&cap_minors_map);
पूर्ण
