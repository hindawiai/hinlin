<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Telemetry communication क्रम Wilco EC
 *
 * Copyright 2019 Google LLC
 *
 * The Wilco Embedded Controller is able to send telemetry data
 * which is useful क्रम enterprise applications. A daemon running on
 * the OS sends a command to the EC via a ग_लिखो() to a अक्षर device,
 * and can पढ़ो the response with a पढ़ो(). The ग_लिखो() request is
 * verअगरied by the driver to ensure that it is perक्रमming only one
 * of the allowlisted commands, and that no extraneous data is
 * being transmitted to the EC. The response is passed directly
 * back to the पढ़ोer with no modअगरication.
 *
 * The अक्षरacter device will appear as /dev/wilco_telemN, where N
 * is some small non-negative पूर्णांकeger, starting with 0. Only one
 * process may have the file descriptor खोलो at a समय. The calling
 * userspace program needs to keep the device file descriptor खोलो
 * between the calls to ग_लिखो() and पढ़ो() in order to preserve the
 * response. Up to 32 bytes will be available क्रम पढ़ोing.
 *
 * For testing purposes, try requesting the EC's firmware build
 * date, by sending the WILCO_EC_TELEM_GET_VERSION command with
 * argument index=3. i.e. ग_लिखो [0x38, 0x00, 0x03]
 * to the device node. An ASCII string of the build date is
 * वापसed.
 */

#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#घोषणा TELEM_DEV_NAME		"wilco_telem"
#घोषणा TELEM_CLASS_NAME	TELEM_DEV_NAME
#घोषणा DRV_NAME		TELEM_DEV_NAME
#घोषणा TELEM_DEV_NAME_FMT	(TELEM_DEV_NAME "%d")
अटल काष्ठा class telem_class = अणु
	.owner	= THIS_MODULE,
	.name	= TELEM_CLASS_NAME,
पूर्ण;

/* Keep track of all the device numbers used. */
#घोषणा TELEM_MAX_DEV 128
अटल पूर्णांक telem_major;
अटल DEFINE_IDA(telem_ida);

/* EC telemetry command codes */
#घोषणा WILCO_EC_TELEM_GET_LOG			0x99
#घोषणा WILCO_EC_TELEM_GET_VERSION		0x38
#घोषणा WILCO_EC_TELEM_GET_FAN_INFO		0x2E
#घोषणा WILCO_EC_TELEM_GET_DIAG_INFO		0xFA
#घोषणा WILCO_EC_TELEM_GET_TEMP_INFO		0x95
#घोषणा WILCO_EC_TELEM_GET_TEMP_READ		0x2C
#घोषणा WILCO_EC_TELEM_GET_BATT_EXT_INFO	0x07
#घोषणा WILCO_EC_TELEM_GET_BATT_PPID_INFO	0x8A

#घोषणा TELEM_ARGS_SIZE_MAX	30

/*
 * The following telem_args_get_* काष्ठाs are embedded within the |args| field
 * of wilco_ec_telem_request.
 */

काष्ठा telem_args_get_log अणु
	u8 log_type;
	u8 log_index;
पूर्ण __packed;

/*
 * Get a piece of info about the EC firmware version:
 * 0 = label
 * 1 = svn_rev
 * 2 = model_no
 * 3 = build_date
 * 4 = frio_version
 */
काष्ठा telem_args_get_version अणु
	u8 index;
पूर्ण __packed;

काष्ठा telem_args_get_fan_info अणु
	u8 command;
	u8 fan_number;
	u8 arg;
पूर्ण __packed;

काष्ठा telem_args_get_diag_info अणु
	u8 type;
	u8 sub_type;
पूर्ण __packed;

काष्ठा telem_args_get_temp_info अणु
	u8 command;
	u8 index;
	u8 field;
	u8 zone;
पूर्ण __packed;

काष्ठा telem_args_get_temp_पढ़ो अणु
	u8 sensor_index;
पूर्ण __packed;

काष्ठा telem_args_get_batt_ext_info अणु
	u8 var_args[5];
पूर्ण __packed;

काष्ठा telem_args_get_batt_ppid_info अणु
	u8 always1; /* Should always be 1 */
पूर्ण __packed;

/**
 * काष्ठा wilco_ec_telem_request - Telemetry command and arguments sent to EC.
 * @command: One of WILCO_EC_TELEM_GET_* command codes.
 * @reserved: Must be 0.
 * @args: The first N bytes are one of telem_args_get_* काष्ठाs, the rest is 0.
 */
काष्ठा wilco_ec_telem_request अणु
	u8 command;
	u8 reserved;
	जोड़ अणु
		u8 buf[TELEM_ARGS_SIZE_MAX];
		काष्ठा telem_args_get_log		get_log;
		काष्ठा telem_args_get_version		get_version;
		काष्ठा telem_args_get_fan_info		get_fan_info;
		काष्ठा telem_args_get_diag_info		get_diag_info;
		काष्ठा telem_args_get_temp_info		get_temp_info;
		काष्ठा telem_args_get_temp_पढ़ो		get_temp_पढ़ो;
		काष्ठा telem_args_get_batt_ext_info	get_batt_ext_info;
		काष्ठा telem_args_get_batt_ppid_info	get_batt_ppid_info;
	पूर्ण args;
पूर्ण __packed;

/**
 * check_telem_request() - Ensure that a request from userspace is valid.
 * @rq: Request buffer copied from userspace.
 * @size: Number of bytes copied from userspace.
 *
 * Return: 0 अगर valid, -EINVAL अगर bad command or reserved byte is non-zero,
 *         -EMSGSIZE अगर the request is too दीर्घ.
 *
 * We करो not want to allow userspace to send arbitrary telemetry commands to
 * the EC. Thereक्रमe we check to ensure that
 * 1. The request follows the क्रमmat of काष्ठा wilco_ec_telem_request.
 * 2. The supplied command code is one of the allowlisted commands.
 * 3. The request only contains the necessary data क्रम the header and arguments.
 */
अटल पूर्णांक check_telem_request(काष्ठा wilco_ec_telem_request *rq,
			       माप_प्रकार size)
अणु
	माप_प्रकार max_size = दुरत्व(काष्ठा wilco_ec_telem_request, args);

	अगर (rq->reserved)
		वापस -EINVAL;

	चयन (rq->command) अणु
	हाल WILCO_EC_TELEM_GET_LOG:
		max_size += माप(rq->args.get_log);
		अवरोध;
	हाल WILCO_EC_TELEM_GET_VERSION:
		max_size += माप(rq->args.get_version);
		अवरोध;
	हाल WILCO_EC_TELEM_GET_FAN_INFO:
		max_size += माप(rq->args.get_fan_info);
		अवरोध;
	हाल WILCO_EC_TELEM_GET_DIAG_INFO:
		max_size += माप(rq->args.get_diag_info);
		अवरोध;
	हाल WILCO_EC_TELEM_GET_TEMP_INFO:
		max_size += माप(rq->args.get_temp_info);
		अवरोध;
	हाल WILCO_EC_TELEM_GET_TEMP_READ:
		max_size += माप(rq->args.get_temp_पढ़ो);
		अवरोध;
	हाल WILCO_EC_TELEM_GET_BATT_EXT_INFO:
		max_size += माप(rq->args.get_batt_ext_info);
		अवरोध;
	हाल WILCO_EC_TELEM_GET_BATT_PPID_INFO:
		अगर (rq->args.get_batt_ppid_info.always1 != 1)
			वापस -EINVAL;

		max_size += माप(rq->args.get_batt_ppid_info);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस (size <= max_size) ? 0 : -EMSGSIZE;
पूर्ण

/**
 * काष्ठा telem_device_data - Data क्रम a Wilco EC device that queries telemetry.
 * @cdev: Char dev that userspace पढ़ोs and polls from.
 * @dev: Device associated with the %cdev.
 * @ec: Wilco EC that we will be communicating with using the mailbox पूर्णांकerface.
 * @available: Boolean of अगर the device can be खोलोed.
 */
काष्ठा telem_device_data अणु
	काष्ठा device dev;
	काष्ठा cdev cdev;
	काष्ठा wilco_ec_device *ec;
	atomic_t available;
पूर्ण;

#घोषणा TELEM_RESPONSE_SIZE	EC_MAILBOX_DATA_SIZE

/**
 * काष्ठा telem_session_data - Data that exists between खोलो() and release().
 * @dev_data: Poपूर्णांकer to get back to the device data and EC.
 * @request: Command and arguments sent to EC.
 * @response: Response buffer of data from EC.
 * @has_msg: Is there data available to पढ़ो from a previous ग_लिखो?
 */
काष्ठा telem_session_data अणु
	काष्ठा telem_device_data *dev_data;
	काष्ठा wilco_ec_telem_request request;
	u8 response[TELEM_RESPONSE_SIZE];
	bool has_msg;
पूर्ण;

/**
 * telem_खोलो() - Callback क्रम when the device node is खोलोed.
 * @inode: inode क्रम this अक्षर device node.
 * @filp: file क्रम this अक्षर device node.
 *
 * We need to ensure that after writing a command to the device,
 * the same userspace process पढ़ोs the corresponding result.
 * Thereक्रमe, we increment a refcount on खोलोing the device, so that
 * only one process can communicate with the EC at a समय.
 *
 * Return: 0 on success, or negative error code on failure.
 */
अटल पूर्णांक telem_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा telem_device_data *dev_data;
	काष्ठा telem_session_data *sess_data;

	/* Ensure device isn't alपढ़ोy खोलो */
	dev_data = container_of(inode->i_cdev, काष्ठा telem_device_data, cdev);
	अगर (atomic_cmpxchg(&dev_data->available, 1, 0) == 0)
		वापस -EBUSY;

	get_device(&dev_data->dev);

	sess_data = kzalloc(माप(*sess_data), GFP_KERNEL);
	अगर (!sess_data) अणु
		atomic_set(&dev_data->available, 1);
		वापस -ENOMEM;
	पूर्ण
	sess_data->dev_data = dev_data;
	sess_data->has_msg = false;

	stream_खोलो(inode, filp);
	filp->निजी_data = sess_data;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार telem_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			   माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा telem_session_data *sess_data = filp->निजी_data;
	काष्ठा wilco_ec_message msg = अणुपूर्ण;
	पूर्णांक ret;

	अगर (count > माप(sess_data->request))
		वापस -EMSGSIZE;
	स_रखो(&sess_data->request, 0, माप(sess_data->request));
	अगर (copy_from_user(&sess_data->request, buf, count))
		वापस -EFAULT;
	ret = check_telem_request(&sess_data->request, count);
	अगर (ret < 0)
		वापस ret;

	स_रखो(sess_data->response, 0, माप(sess_data->response));
	msg.type = WILCO_EC_MSG_TELEMETRY;
	msg.request_data = &sess_data->request;
	msg.request_size = माप(sess_data->request);
	msg.response_data = sess_data->response;
	msg.response_size = माप(sess_data->response);

	ret = wilco_ec_mailbox(sess_data->dev_data->ec, &msg);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != माप(sess_data->response))
		वापस -EMSGSIZE;

	sess_data->has_msg = true;

	वापस count;
पूर्ण

अटल sमाप_प्रकार telem_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			  loff_t *pos)
अणु
	काष्ठा telem_session_data *sess_data = filp->निजी_data;

	अगर (!sess_data->has_msg)
		वापस -ENODATA;
	अगर (count > माप(sess_data->response))
		वापस -EINVAL;

	अगर (copy_to_user(buf, sess_data->response, count))
		वापस -EFAULT;

	sess_data->has_msg = false;

	वापस count;
पूर्ण

अटल पूर्णांक telem_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा telem_session_data *sess_data = filp->निजी_data;

	atomic_set(&sess_data->dev_data->available, 1);
	put_device(&sess_data->dev_data->dev);
	kमुक्त(sess_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations telem_fops = अणु
	.खोलो = telem_खोलो,
	.ग_लिखो = telem_ग_लिखो,
	.पढ़ो = telem_पढ़ो,
	.release = telem_release,
	.llseek = no_llseek,
	.owner = THIS_MODULE,
पूर्ण;

/**
 * telem_device_मुक्त() - Callback to मुक्त the telem_device_data काष्ठाure.
 * @d: The device embedded in our device data, which we have been ref counting.
 *
 * Once all खोलो file descriptors are बंदd and the device has been हटाओd,
 * the refcount of the device will fall to 0 and this will be called.
 */
अटल व्योम telem_device_मुक्त(काष्ठा device *d)
अणु
	काष्ठा telem_device_data *dev_data;

	dev_data = container_of(d, काष्ठा telem_device_data, dev);
	kमुक्त(dev_data);
पूर्ण

/**
 * telem_device_probe() - Callback when creating a new device.
 * @pdev: platक्रमm device that we will be receiving telems from.
 *
 * This finds a मुक्त minor number क्रम the device, allocates and initializes
 * some device data, and creates a new device and अक्षर dev node.
 *
 * Return: 0 on success, negative error code on failure.
 */
अटल पूर्णांक telem_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा telem_device_data *dev_data;
	पूर्णांक error, minor;

	/* Get the next available device number */
	minor = ida_alloc_max(&telem_ida, TELEM_MAX_DEV-1, GFP_KERNEL);
	अगर (minor < 0) अणु
		error = minor;
		dev_err(&pdev->dev, "Failed to find minor number: %d\n", error);
		वापस error;
	पूर्ण

	dev_data = kzalloc(माप(*dev_data), GFP_KERNEL);
	अगर (!dev_data) अणु
		ida_simple_हटाओ(&telem_ida, minor);
		वापस -ENOMEM;
	पूर्ण

	/* Initialize the device data */
	dev_data->ec = dev_get_platdata(&pdev->dev);
	atomic_set(&dev_data->available, 1);
	platक्रमm_set_drvdata(pdev, dev_data);

	/* Initialize the device */
	dev_data->dev.devt = MKDEV(telem_major, minor);
	dev_data->dev.class = &telem_class;
	dev_data->dev.release = telem_device_मुक्त;
	dev_set_name(&dev_data->dev, TELEM_DEV_NAME_FMT, minor);
	device_initialize(&dev_data->dev);

	/* Initialize the अक्षरacter device and add it to userspace */;
	cdev_init(&dev_data->cdev, &telem_fops);
	error = cdev_device_add(&dev_data->cdev, &dev_data->dev);
	अगर (error) अणु
		put_device(&dev_data->dev);
		ida_simple_हटाओ(&telem_ida, minor);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक telem_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा telem_device_data *dev_data = platक्रमm_get_drvdata(pdev);

	cdev_device_del(&dev_data->cdev, &dev_data->dev);
	ida_simple_हटाओ(&telem_ida, MINOR(dev_data->dev.devt));
	put_device(&dev_data->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver telem_driver = अणु
	.probe = telem_device_probe,
	.हटाओ = telem_device_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init telem_module_init(व्योम)
अणु
	dev_t dev_num = 0;
	पूर्णांक ret;

	ret = class_रेजिस्टर(&telem_class);
	अगर (ret) अणु
		pr_err(DRV_NAME ": Failed registering class: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Request the kernel क्रम device numbers, starting with minor=0 */
	ret = alloc_chrdev_region(&dev_num, 0, TELEM_MAX_DEV, TELEM_DEV_NAME);
	अगर (ret) अणु
		pr_err(DRV_NAME ": Failed allocating dev numbers: %d\n", ret);
		जाओ destroy_class;
	पूर्ण
	telem_major = MAJOR(dev_num);

	ret = platक्रमm_driver_रेजिस्टर(&telem_driver);
	अगर (ret < 0) अणु
		pr_err(DRV_NAME ": Failed registering driver: %d\n", ret);
		जाओ unरेजिस्टर_region;
	पूर्ण

	वापस 0;

unरेजिस्टर_region:
	unरेजिस्टर_chrdev_region(MKDEV(telem_major, 0), TELEM_MAX_DEV);
destroy_class:
	class_unरेजिस्टर(&telem_class);
	ida_destroy(&telem_ida);
	वापस ret;
पूर्ण

अटल व्योम __निकास telem_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&telem_driver);
	unरेजिस्टर_chrdev_region(MKDEV(telem_major, 0), TELEM_MAX_DEV);
	class_unरेजिस्टर(&telem_class);
	ida_destroy(&telem_ida);
पूर्ण

module_init(telem_module_init);
module_निकास(telem_module_निकास);

MODULE_AUTHOR("Nick Crews <ncrews@chromium.org>");
MODULE_DESCRIPTION("Wilco EC telemetry driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
