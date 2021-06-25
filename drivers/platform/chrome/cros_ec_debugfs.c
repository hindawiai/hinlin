<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Debug logs क्रम the ChromeOS EC
//
// Copyright (C) 2015 Google, Inc.

#समावेश <linux/circ_buf.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#घोषणा DRV_NAME "cros-ec-debugfs"

#घोषणा LOG_SHIFT		14
#घोषणा LOG_SIZE		(1 << LOG_SHIFT)
#घोषणा LOG_POLL_SEC		10

#घोषणा CIRC_ADD(idx, size, value)	(((idx) + (value)) & ((size) - 1))

/**
 * काष्ठा cros_ec_debugfs - EC debugging inक्रमmation.
 *
 * @ec: EC device this debugfs inक्रमmation beदीर्घs to
 * @dir: dentry क्रम debugfs files
 * @log_buffer: circular buffer क्रम console log inक्रमmation
 * @पढ़ो_msg: pपुनः_स्मृतिated EC command and buffer to पढ़ो console log
 * @log_mutex: mutex to protect circular buffer
 * @log_wq: रुकोqueue क्रम log पढ़ोers
 * @log_poll_work: recurring task to poll EC क्रम new console log data
 * @panicinfo_blob: panicinfo debugfs blob
 */
काष्ठा cros_ec_debugfs अणु
	काष्ठा cros_ec_dev *ec;
	काष्ठा dentry *dir;
	/* EC log */
	काष्ठा circ_buf log_buffer;
	काष्ठा cros_ec_command *पढ़ो_msg;
	काष्ठा mutex log_mutex;
	रुको_queue_head_t log_wq;
	काष्ठा delayed_work log_poll_work;
	/* EC panicinfo */
	काष्ठा debugfs_blob_wrapper panicinfo_blob;
पूर्ण;

/*
 * We need to make sure that the EC log buffer on the UART is large enough,
 * so that it is unlikely enough to overlow within LOG_POLL_SEC.
 */
अटल व्योम cros_ec_console_log_work(काष्ठा work_काष्ठा *__work)
अणु
	काष्ठा cros_ec_debugfs *debug_info =
		container_of(to_delayed_work(__work),
			     काष्ठा cros_ec_debugfs,
			     log_poll_work);
	काष्ठा cros_ec_dev *ec = debug_info->ec;
	काष्ठा circ_buf *cb = &debug_info->log_buffer;
	काष्ठा cros_ec_command snapshot_msg = अणु
		.command = EC_CMD_CONSOLE_SNAPSHOT + ec->cmd_offset,
	पूर्ण;

	काष्ठा ec_params_console_पढ़ो_v1 *पढ़ो_params =
		(काष्ठा ec_params_console_पढ़ो_v1 *)debug_info->पढ़ो_msg->data;
	uपूर्णांक8_t *ec_buffer = (uपूर्णांक8_t *)debug_info->पढ़ो_msg->data;
	पूर्णांक idx;
	पूर्णांक buf_space;
	पूर्णांक ret;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, &snapshot_msg);
	अगर (ret < 0)
		जाओ resched;

	/* Loop until we have पढ़ो everything, or there's an error. */
	mutex_lock(&debug_info->log_mutex);
	buf_space = CIRC_SPACE(cb->head, cb->tail, LOG_SIZE);

	जबतक (1) अणु
		अगर (!buf_space) अणु
			dev_info_once(ec->dev,
				      "Some logs may have been dropped...\n");
			अवरोध;
		पूर्ण

		स_रखो(पढ़ो_params, '\0', माप(*पढ़ो_params));
		पढ़ो_params->subcmd = CONSOLE_READ_RECENT;
		ret = cros_ec_cmd_xfer_status(ec->ec_dev,
					      debug_info->पढ़ो_msg);
		अगर (ret < 0)
			अवरोध;

		/* If the buffer is empty, we're करोne here. */
		अगर (ret == 0 || ec_buffer[0] == '\0')
			अवरोध;

		idx = 0;
		जबतक (idx < ret && ec_buffer[idx] != '\0' && buf_space > 0) अणु
			cb->buf[cb->head] = ec_buffer[idx];
			cb->head = CIRC_ADD(cb->head, LOG_SIZE, 1);
			idx++;
			buf_space--;
		पूर्ण

		wake_up(&debug_info->log_wq);
	पूर्ण

	mutex_unlock(&debug_info->log_mutex);

resched:
	schedule_delayed_work(&debug_info->log_poll_work,
			      msecs_to_jअगरfies(LOG_POLL_SEC * 1000));
पूर्ण

अटल पूर्णांक cros_ec_console_log_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = inode->i_निजी;

	वापस stream_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार cros_ec_console_log_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cros_ec_debugfs *debug_info = file->निजी_data;
	काष्ठा circ_buf *cb = &debug_info->log_buffer;
	sमाप_प्रकार ret;

	mutex_lock(&debug_info->log_mutex);

	जबतक (!CIRC_CNT(cb->head, cb->tail, LOG_SIZE)) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
			जाओ error;
		पूर्ण

		mutex_unlock(&debug_info->log_mutex);

		ret = रुको_event_पूर्णांकerruptible(debug_info->log_wq,
					CIRC_CNT(cb->head, cb->tail, LOG_SIZE));
		अगर (ret < 0)
			वापस ret;

		mutex_lock(&debug_info->log_mutex);
	पूर्ण

	/* Only copy until the end of the circular buffer, and let userspace
	 * retry to get the rest of the data.
	 */
	ret = min_t(माप_प्रकार, CIRC_CNT_TO_END(cb->head, cb->tail, LOG_SIZE),
		    count);

	अगर (copy_to_user(buf, cb->buf + cb->tail, ret)) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	cb->tail = CIRC_ADD(cb->tail, LOG_SIZE, ret);

error:
	mutex_unlock(&debug_info->log_mutex);
	वापस ret;
पूर्ण

अटल __poll_t cros_ec_console_log_poll(काष्ठा file *file,
					     poll_table *रुको)
अणु
	काष्ठा cros_ec_debugfs *debug_info = file->निजी_data;
	__poll_t mask = 0;

	poll_रुको(file, &debug_info->log_wq, रुको);

	mutex_lock(&debug_info->log_mutex);
	अगर (CIRC_CNT(debug_info->log_buffer.head,
		     debug_info->log_buffer.tail,
		     LOG_SIZE))
		mask |= EPOLLIN | EPOLLRDNORM;
	mutex_unlock(&debug_info->log_mutex);

	वापस mask;
पूर्ण

अटल पूर्णांक cros_ec_console_log_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार cros_ec_pdinfo_पढ़ो(काष्ठा file *file,
				   अक्षर __user *user_buf,
				   माप_प्रकार count,
				   loff_t *ppos)
अणु
	अक्षर पढ़ो_buf[EC_USB_PD_MAX_PORTS * 40], *p = पढ़ो_buf;
	काष्ठा cros_ec_debugfs *debug_info = file->निजी_data;
	काष्ठा cros_ec_device *ec_dev = debug_info->ec->ec_dev;
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		जोड़ अणु
			काष्ठा ec_response_usb_pd_control_v1 resp;
			काष्ठा ec_params_usb_pd_control params;
		पूर्ण;
	पूर्ण __packed ec_buf;
	काष्ठा cros_ec_command *msg;
	काष्ठा ec_response_usb_pd_control_v1 *resp;
	काष्ठा ec_params_usb_pd_control *params;
	पूर्णांक i;

	msg = &ec_buf.msg;
	params = (काष्ठा ec_params_usb_pd_control *)msg->data;
	resp = (काष्ठा ec_response_usb_pd_control_v1 *)msg->data;

	msg->command = EC_CMD_USB_PD_CONTROL;
	msg->version = 1;
	msg->insize = माप(*resp);
	msg->outsize = माप(*params);

	/*
	 * Read status from all PD ports until failure, typically caused
	 * by attempting to पढ़ो status on a port that करोesn't exist.
	 */
	क्रम (i = 0; i < EC_USB_PD_MAX_PORTS; ++i) अणु
		params->port = i;
		params->role = 0;
		params->mux = 0;
		params->swap = 0;

		अगर (cros_ec_cmd_xfer_status(ec_dev, msg) < 0)
			अवरोध;

		p += scnम_लिखो(p, माप(पढ़ो_buf) + पढ़ो_buf - p,
			       "p%d: %s en:%.2x role:%.2x pol:%.2x\n", i,
			       resp->state, resp->enabled, resp->role,
			       resp->polarity);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       पढ़ो_buf, p - पढ़ो_buf);
पूर्ण

अटल bool cros_ec_upसमय_is_supported(काष्ठा cros_ec_device *ec_dev)
अणु
	काष्ठा अणु
		काष्ठा cros_ec_command cmd;
		काष्ठा ec_response_upसमय_info resp;
	पूर्ण __packed msg = अणुपूर्ण;
	पूर्णांक ret;

	msg.cmd.command = EC_CMD_GET_UPTIME_INFO;
	msg.cmd.insize = माप(msg.resp);

	ret = cros_ec_cmd_xfer_status(ec_dev, &msg.cmd);
	अगर (ret == -EPROTO && msg.cmd.result == EC_RES_INVALID_COMMAND)
		वापस false;

	/* Other errors maybe a transient error, करो not rule about support. */
	वापस true;
पूर्ण

अटल sमाप_प्रकार cros_ec_upसमय_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cros_ec_debugfs *debug_info = file->निजी_data;
	काष्ठा cros_ec_device *ec_dev = debug_info->ec->ec_dev;
	काष्ठा अणु
		काष्ठा cros_ec_command cmd;
		काष्ठा ec_response_upसमय_info resp;
	पूर्ण __packed msg = अणुपूर्ण;
	काष्ठा ec_response_upसमय_info *resp;
	अक्षर पढ़ो_buf[32];
	पूर्णांक ret;

	resp = (काष्ठा ec_response_upसमय_info *)&msg.resp;

	msg.cmd.command = EC_CMD_GET_UPTIME_INFO;
	msg.cmd.insize = माप(*resp);

	ret = cros_ec_cmd_xfer_status(ec_dev, &msg.cmd);
	अगर (ret < 0)
		वापस ret;

	ret = scnम_लिखो(पढ़ो_buf, माप(पढ़ो_buf), "%u\n",
			resp->समय_since_ec_boot_ms);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, पढ़ो_buf, ret);
पूर्ण

अटल स्थिर काष्ठा file_operations cros_ec_console_log_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = cros_ec_console_log_खोलो,
	.पढ़ो = cros_ec_console_log_पढ़ो,
	.llseek = no_llseek,
	.poll = cros_ec_console_log_poll,
	.release = cros_ec_console_log_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations cros_ec_pdinfo_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = cros_ec_pdinfo_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations cros_ec_upसमय_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = cros_ec_upसमय_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक ec_पढ़ो_version_supported(काष्ठा cros_ec_dev *ec)
अणु
	काष्ठा ec_params_get_cmd_versions_v1 *params;
	काष्ठा ec_response_get_cmd_versions *response;
	पूर्णांक ret;

	काष्ठा cros_ec_command *msg;

	msg = kzalloc(माप(*msg) + max(माप(*params), माप(*response)),
		GFP_KERNEL);
	अगर (!msg)
		वापस 0;

	msg->command = EC_CMD_GET_CMD_VERSIONS + ec->cmd_offset;
	msg->outsize = माप(*params);
	msg->insize = माप(*response);

	params = (काष्ठा ec_params_get_cmd_versions_v1 *)msg->data;
	params->cmd = EC_CMD_CONSOLE_READ;
	response = (काष्ठा ec_response_get_cmd_versions *)msg->data;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg) >= 0 &&
	      response->version_mask & EC_VER_MASK(1);

	kमुक्त(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_create_console_log(काष्ठा cros_ec_debugfs *debug_info)
अणु
	काष्ठा cros_ec_dev *ec = debug_info->ec;
	अक्षर *buf;
	पूर्णांक पढ़ो_params_size;
	पूर्णांक पढ़ो_response_size;

	/*
	 * If the console log feature is not supported वापस silently and
	 * करोn't create the console_log entry.
	 */
	अगर (!ec_पढ़ो_version_supported(ec))
		वापस 0;

	buf = devm_kzalloc(ec->dev, LOG_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	पढ़ो_params_size = माप(काष्ठा ec_params_console_पढ़ो_v1);
	पढ़ो_response_size = ec->ec_dev->max_response;
	debug_info->पढ़ो_msg = devm_kzalloc(ec->dev,
		माप(*debug_info->पढ़ो_msg) +
			max(पढ़ो_params_size, पढ़ो_response_size), GFP_KERNEL);
	अगर (!debug_info->पढ़ो_msg)
		वापस -ENOMEM;

	debug_info->पढ़ो_msg->version = 1;
	debug_info->पढ़ो_msg->command = EC_CMD_CONSOLE_READ + ec->cmd_offset;
	debug_info->पढ़ो_msg->outsize = पढ़ो_params_size;
	debug_info->पढ़ो_msg->insize = पढ़ो_response_size;

	debug_info->log_buffer.buf = buf;
	debug_info->log_buffer.head = 0;
	debug_info->log_buffer.tail = 0;

	mutex_init(&debug_info->log_mutex);
	init_रुकोqueue_head(&debug_info->log_wq);

	debugfs_create_file("console_log", S_IFREG | 0444, debug_info->dir,
			    debug_info, &cros_ec_console_log_fops);

	INIT_DELAYED_WORK(&debug_info->log_poll_work,
			  cros_ec_console_log_work);
	schedule_delayed_work(&debug_info->log_poll_work, 0);

	वापस 0;
पूर्ण

अटल व्योम cros_ec_cleanup_console_log(काष्ठा cros_ec_debugfs *debug_info)
अणु
	अगर (debug_info->log_buffer.buf) अणु
		cancel_delayed_work_sync(&debug_info->log_poll_work);
		mutex_destroy(&debug_info->log_mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक cros_ec_create_panicinfo(काष्ठा cros_ec_debugfs *debug_info)
अणु
	काष्ठा cros_ec_device *ec_dev = debug_info->ec->ec_dev;
	पूर्णांक ret;
	काष्ठा cros_ec_command *msg;
	पूर्णांक insize;

	insize = ec_dev->max_response;

	msg = devm_kzalloc(debug_info->ec->dev,
			माप(*msg) + insize, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->command = EC_CMD_GET_PANIC_INFO;
	msg->insize = insize;

	ret = cros_ec_cmd_xfer_status(ec_dev, msg);
	अगर (ret < 0) अणु
		ret = 0;
		जाओ मुक्त;
	पूर्ण

	/* No panic data */
	अगर (ret == 0)
		जाओ मुक्त;

	debug_info->panicinfo_blob.data = msg->data;
	debug_info->panicinfo_blob.size = ret;

	debugfs_create_blob("panicinfo", S_IFREG | 0444, debug_info->dir,
			    &debug_info->panicinfo_blob);

	वापस 0;

मुक्त:
	devm_kमुक्त(debug_info->ec->dev, msg);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_debugfs_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec = dev_get_drvdata(pd->dev.parent);
	काष्ठा cros_ec_platक्रमm *ec_platक्रमm = dev_get_platdata(ec->dev);
	स्थिर अक्षर *name = ec_platक्रमm->ec_name;
	काष्ठा cros_ec_debugfs *debug_info;
	पूर्णांक ret;

	debug_info = devm_kzalloc(ec->dev, माप(*debug_info), GFP_KERNEL);
	अगर (!debug_info)
		वापस -ENOMEM;

	debug_info->ec = ec;
	debug_info->dir = debugfs_create_dir(name, शून्य);

	ret = cros_ec_create_panicinfo(debug_info);
	अगर (ret)
		जाओ हटाओ_debugfs;

	ret = cros_ec_create_console_log(debug_info);
	अगर (ret)
		जाओ हटाओ_debugfs;

	debugfs_create_file("pdinfo", 0444, debug_info->dir, debug_info,
			    &cros_ec_pdinfo_fops);

	अगर (cros_ec_upसमय_is_supported(ec->ec_dev))
		debugfs_create_file("uptime", 0444, debug_info->dir, debug_info,
				    &cros_ec_upसमय_fops);

	debugfs_create_x32("last_resume_result", 0444, debug_info->dir,
			   &ec->ec_dev->last_resume_result);

	ec->debug_info = debug_info;

	dev_set_drvdata(&pd->dev, ec);

	वापस 0;

हटाओ_debugfs:
	debugfs_हटाओ_recursive(debug_info->dir);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_debugfs_हटाओ(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec = dev_get_drvdata(pd->dev.parent);

	debugfs_हटाओ_recursive(ec->debug_info->dir);
	cros_ec_cleanup_console_log(ec->debug_info);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cros_ec_debugfs_suspend(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_dev *ec = dev_get_drvdata(dev);

	अगर (ec->debug_info->log_buffer.buf)
		cancel_delayed_work_sync(&ec->debug_info->log_poll_work);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cros_ec_debugfs_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_dev *ec = dev_get_drvdata(dev);

	अगर (ec->debug_info->log_buffer.buf)
		schedule_delayed_work(&ec->debug_info->log_poll_work, 0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cros_ec_debugfs_pm_ops,
			 cros_ec_debugfs_suspend, cros_ec_debugfs_resume);

अटल काष्ठा platक्रमm_driver cros_ec_debugfs_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &cros_ec_debugfs_pm_ops,
	पूर्ण,
	.probe = cros_ec_debugfs_probe,
	.हटाओ = cros_ec_debugfs_हटाओ,
पूर्ण;

module_platक्रमm_driver(cros_ec_debugfs_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Debug logs for ChromeOS EC");
MODULE_ALIAS("platform:" DRV_NAME);
