<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Miscellaneous अक्षरacter driver क्रम ChromeOS Embedded Controller
 *
 * Copyright 2014 Google, Inc.
 * Copyright 2019 Google LLC
 *
 * This file is a rework and part of the code is ported from
 * drivers/mfd/cros_ec_dev.c that was originally written by
 * Bill Riअक्षरdson.
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_data/cros_ec_अक्षरdev.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#घोषणा DRV_NAME		"cros-ec-chardev"

/* Arbitrary bounded size क्रम the event queue */
#घोषणा CROS_MAX_EVENT_LEN	PAGE_SIZE

काष्ठा अक्षरdev_data अणु
	काष्ठा cros_ec_dev *ec_dev;
	काष्ठा miscdevice misc;
पूर्ण;

काष्ठा अक्षरdev_priv अणु
	काष्ठा cros_ec_dev *ec_dev;
	काष्ठा notअगरier_block notअगरier;
	रुको_queue_head_t रुको_event;
	अचिन्हित दीर्घ event_mask;
	काष्ठा list_head events;
	माप_प्रकार event_len;
पूर्ण;

काष्ठा ec_event अणु
	काष्ठा list_head node;
	माप_प्रकार size;
	u8 event_type;
	u8 data[];
पूर्ण;

अटल पूर्णांक ec_get_version(काष्ठा cros_ec_dev *ec, अक्षर *str, पूर्णांक maxlen)
अणु
	अटल स्थिर अक्षर * स्थिर current_image_name[] = अणु
		"unknown", "read-only", "read-write", "invalid",
	पूर्ण;
	काष्ठा ec_response_get_version *resp;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kzalloc(माप(*msg) + माप(*resp), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->command = EC_CMD_GET_VERSION + ec->cmd_offset;
	msg->insize = माप(*resp);

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0) अणु
		snम_लिखो(str, maxlen,
			 "Unknown EC version, returned error: %d\n",
			 msg->result);
		जाओ निकास;
	पूर्ण

	resp = (काष्ठा ec_response_get_version *)msg->data;
	अगर (resp->current_image >= ARRAY_SIZE(current_image_name))
		resp->current_image = 3; /* invalid */

	snम_लिखो(str, maxlen, "%s\n%s\n%s\n%s\n", CROS_EC_DEV_VERSION,
		 resp->version_string_ro, resp->version_string_rw,
		 current_image_name[resp->current_image]);

	ret = 0;
निकास:
	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_अक्षरdev_mkbp_event(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ queued_during_suspend,
				      व्योम *_notअगरy)
अणु
	काष्ठा अक्षरdev_priv *priv = container_of(nb, काष्ठा अक्षरdev_priv,
						 notअगरier);
	काष्ठा cros_ec_device *ec_dev = priv->ec_dev->ec_dev;
	काष्ठा ec_event *event;
	अचिन्हित दीर्घ event_bit = 1 << ec_dev->event_data.event_type;
	पूर्णांक total_size = माप(*event) + ec_dev->event_size;

	अगर (!(event_bit & priv->event_mask) ||
	    (priv->event_len + total_size) > CROS_MAX_EVENT_LEN)
		वापस NOTIFY_DONE;

	event = kzalloc(total_size, GFP_KERNEL);
	अगर (!event)
		वापस NOTIFY_DONE;

	event->size = ec_dev->event_size;
	event->event_type = ec_dev->event_data.event_type;
	स_नकल(event->data, &ec_dev->event_data.data, ec_dev->event_size);

	spin_lock(&priv->रुको_event.lock);
	list_add_tail(&event->node, &priv->events);
	priv->event_len += total_size;
	wake_up_locked(&priv->रुको_event);
	spin_unlock(&priv->रुको_event.lock);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा ec_event *cros_ec_अक्षरdev_fetch_event(काष्ठा अक्षरdev_priv *priv,
						    bool fetch, bool block)
अणु
	काष्ठा ec_event *event;
	पूर्णांक err;

	spin_lock(&priv->रुको_event.lock);
	अगर (!block && list_empty(&priv->events)) अणु
		event = ERR_PTR(-EWOULDBLOCK);
		जाओ out;
	पूर्ण

	अगर (!fetch) अणु
		event = शून्य;
		जाओ out;
	पूर्ण

	err = रुको_event_पूर्णांकerruptible_locked(priv->रुको_event,
					      !list_empty(&priv->events));
	अगर (err) अणु
		event = ERR_PTR(err);
		जाओ out;
	पूर्ण

	event = list_first_entry(&priv->events, काष्ठा ec_event, node);
	list_del(&event->node);
	priv->event_len -= माप(*event) + event->size;

out:
	spin_unlock(&priv->रुको_event.lock);
	वापस event;
पूर्ण

/*
 * Device file ops
 */
अटल पूर्णांक cros_ec_अक्षरdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा miscdevice *mdev = filp->निजी_data;
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(mdev->parent);
	काष्ठा अक्षरdev_priv *priv;
	पूर्णांक ret;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->ec_dev = ec_dev;
	filp->निजी_data = priv;
	INIT_LIST_HEAD(&priv->events);
	init_रुकोqueue_head(&priv->रुको_event);
	nonseekable_खोलो(inode, filp);

	priv->notअगरier.notअगरier_call = cros_ec_अक्षरdev_mkbp_event;
	ret = blocking_notअगरier_chain_रेजिस्टर(&ec_dev->ec_dev->event_notअगरier,
					       &priv->notअगरier);
	अगर (ret) अणु
		dev_err(ec_dev->dev, "failed to register event notifier\n");
		kमुक्त(priv);
	पूर्ण

	वापस ret;
पूर्ण

अटल __poll_t cros_ec_अक्षरdev_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा अक्षरdev_priv *priv = filp->निजी_data;

	poll_रुको(filp, &priv->रुको_event, रुको);

	अगर (list_empty(&priv->events))
		वापस 0;

	वापस EPOLLIN | EPOLLRDNORM;
पूर्ण

अटल sमाप_प्रकार cros_ec_अक्षरdev_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				     माप_प्रकार length, loff_t *offset)
अणु
	अक्षर msg[माप(काष्ठा ec_response_get_version) +
		 माप(CROS_EC_DEV_VERSION)];
	काष्ठा अक्षरdev_priv *priv = filp->निजी_data;
	काष्ठा cros_ec_dev *ec_dev = priv->ec_dev;
	माप_प्रकार count;
	पूर्णांक ret;

	अगर (priv->event_mask) अणु /* queued MKBP event */
		काष्ठा ec_event *event;

		event = cros_ec_अक्षरdev_fetch_event(priv, length != 0,
						!(filp->f_flags & O_NONBLOCK));
		अगर (IS_ERR(event))
			वापस PTR_ERR(event);
		/*
		 * length == 0 is special - no IO is करोne but we check
		 * क्रम error conditions.
		 */
		अगर (length == 0)
			वापस 0;

		/* The event is 1 byte of type plus the payload */
		count = min(length, event->size + 1);
		ret = copy_to_user(buffer, &event->event_type, count);
		kमुक्त(event);
		अगर (ret) /* the copy failed */
			वापस -EFAULT;
		*offset = count;
		वापस count;
	पूर्ण

	/*
	 * Legacy behavior अगर no event mask is defined
	 */
	अगर (*offset != 0)
		वापस 0;

	ret = ec_get_version(ec_dev, msg, माप(msg));
	अगर (ret)
		वापस ret;

	count = min(length, म_माप(msg));

	अगर (copy_to_user(buffer, msg, count))
		वापस -EFAULT;

	*offset = count;
	वापस count;
पूर्ण

अटल पूर्णांक cros_ec_अक्षरdev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा अक्षरdev_priv *priv = filp->निजी_data;
	काष्ठा cros_ec_dev *ec_dev = priv->ec_dev;
	काष्ठा ec_event *event, *e;

	blocking_notअगरier_chain_unरेजिस्टर(&ec_dev->ec_dev->event_notअगरier,
					   &priv->notअगरier);

	list_क्रम_each_entry_safe(event, e, &priv->events, node) अणु
		list_del(&event->node);
		kमुक्त(event);
	पूर्ण
	kमुक्त(priv);

	वापस 0;
पूर्ण

/*
 * Ioctls
 */
अटल दीर्घ cros_ec_अक्षरdev_ioctl_xcmd(काष्ठा cros_ec_dev *ec, व्योम __user *arg)
अणु
	काष्ठा cros_ec_command *s_cmd;
	काष्ठा cros_ec_command u_cmd;
	दीर्घ ret;

	अगर (copy_from_user(&u_cmd, arg, माप(u_cmd)))
		वापस -EFAULT;

	अगर (u_cmd.outsize > EC_MAX_MSG_BYTES ||
	    u_cmd.insize > EC_MAX_MSG_BYTES)
		वापस -EINVAL;

	s_cmd = kदो_स्मृति(माप(*s_cmd) + max(u_cmd.outsize, u_cmd.insize),
			GFP_KERNEL);
	अगर (!s_cmd)
		वापस -ENOMEM;

	अगर (copy_from_user(s_cmd, arg, माप(*s_cmd) + u_cmd.outsize)) अणु
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण

	अगर (u_cmd.outsize != s_cmd->outsize ||
	    u_cmd.insize != s_cmd->insize) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	s_cmd->command += ec->cmd_offset;
	ret = cros_ec_cmd_xfer_status(ec->ec_dev, s_cmd);
	/* Only copy data to userland अगर data was received. */
	अगर (ret < 0)
		जाओ निकास;

	अगर (copy_to_user(arg, s_cmd, माप(*s_cmd) + s_cmd->insize))
		ret = -EFAULT;
निकास:
	kमुक्त(s_cmd);
	वापस ret;
पूर्ण

अटल दीर्घ cros_ec_अक्षरdev_ioctl_पढ़ोmem(काष्ठा cros_ec_dev *ec,
					   व्योम __user *arg)
अणु
	काष्ठा cros_ec_device *ec_dev = ec->ec_dev;
	काष्ठा cros_ec_पढ़ोmem s_mem = अणु पूर्ण;
	दीर्घ num;

	/* Not every platक्रमm supports direct पढ़ोs */
	अगर (!ec_dev->cmd_पढ़ोmem)
		वापस -ENOTTY;

	अगर (copy_from_user(&s_mem, arg, माप(s_mem)))
		वापस -EFAULT;

	num = ec_dev->cmd_पढ़ोmem(ec_dev, s_mem.offset, s_mem.bytes,
				  s_mem.buffer);
	अगर (num <= 0)
		वापस num;

	अगर (copy_to_user((व्योम __user *)arg, &s_mem, माप(s_mem)))
		वापस -EFAULT;

	वापस num;
पूर्ण

अटल दीर्घ cros_ec_अक्षरdev_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा अक्षरdev_priv *priv = filp->निजी_data;
	काष्ठा cros_ec_dev *ec = priv->ec_dev;

	अगर (_IOC_TYPE(cmd) != CROS_EC_DEV_IOC)
		वापस -ENOTTY;

	चयन (cmd) अणु
	हाल CROS_EC_DEV_IOCXCMD:
		वापस cros_ec_अक्षरdev_ioctl_xcmd(ec, (व्योम __user *)arg);
	हाल CROS_EC_DEV_IOCRDMEM:
		वापस cros_ec_अक्षरdev_ioctl_पढ़ोmem(ec, (व्योम __user *)arg);
	हाल CROS_EC_DEV_IOCEVENTMASK:
		priv->event_mask = arg;
		वापस 0;
	पूर्ण

	वापस -ENOTTY;
पूर्ण

अटल स्थिर काष्ठा file_operations अक्षरdev_fops = अणु
	.खोलो		= cros_ec_अक्षरdev_खोलो,
	.poll		= cros_ec_अक्षरdev_poll,
	.पढ़ो		= cros_ec_अक्षरdev_पढ़ो,
	.release	= cros_ec_अक्षरdev_release,
	.unlocked_ioctl	= cros_ec_अक्षरdev_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= cros_ec_अक्षरdev_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक cros_ec_अक्षरdev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा cros_ec_platक्रमm *ec_platक्रमm = dev_get_platdata(ec_dev->dev);
	काष्ठा अक्षरdev_data *data;

	/* Create a अक्षर device: we want to create it anew */
	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->ec_dev = ec_dev;
	data->misc.minor = MISC_DYNAMIC_MINOR;
	data->misc.fops = &अक्षरdev_fops;
	data->misc.name = ec_platक्रमm->ec_name;
	data->misc.parent = pdev->dev.parent;

	dev_set_drvdata(&pdev->dev, data);

	वापस misc_रेजिस्टर(&data->misc);
पूर्ण

अटल पूर्णांक cros_ec_अक्षरdev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा अक्षरdev_data *data = dev_get_drvdata(&pdev->dev);

	misc_deरेजिस्टर(&data->misc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cros_ec_अक्षरdev_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = cros_ec_अक्षरdev_probe,
	.हटाओ = cros_ec_अक्षरdev_हटाओ,
पूर्ण;

module_platक्रमm_driver(cros_ec_अक्षरdev_driver);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_AUTHOR("Enric Balletbo i Serra <enric.balletbo@collabora.com>");
MODULE_DESCRIPTION("ChromeOS EC Miscellaneous Character Driver");
MODULE_LICENSE("GPL");
