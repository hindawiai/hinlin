<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/cdev.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uuid.h>
#समावेश <linux/compat.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "client.h"

अटल काष्ठा class *mei_class;
अटल dev_t mei_devt;
#घोषणा MEI_MAX_DEVS  MINORMASK
अटल DEFINE_MUTEX(mei_minor_lock);
अटल DEFINE_IDR(mei_idr);

/**
 * mei_खोलो - the खोलो function
 *
 * @inode: poपूर्णांकer to inode काष्ठाure
 * @file: poपूर्णांकer to file काष्ठाure
 *
 * Return: 0 on success, <0 on error
 */
अटल पूर्णांक mei_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl *cl;

	पूर्णांक err;

	dev = container_of(inode->i_cdev, काष्ठा mei_device, cdev);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->device_lock);

	अगर (dev->dev_state != MEI_DEV_ENABLED) अणु
		dev_dbg(dev->dev, "dev_state != MEI_ENABLED  dev_state = %s\n",
		    mei_dev_state_str(dev->dev_state));
		err = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	cl = mei_cl_alloc_linked(dev);
	अगर (IS_ERR(cl)) अणु
		err = PTR_ERR(cl);
		जाओ err_unlock;
	पूर्ण

	cl->fp = file;
	file->निजी_data = cl;

	mutex_unlock(&dev->device_lock);

	वापस nonseekable_खोलो(inode, file);

err_unlock:
	mutex_unlock(&dev->device_lock);
	वापस err;
पूर्ण

/**
 * mei_cl_vtag_हटाओ_by_fp - हटाओ vtag that corresponds to fp from list
 *
 * @cl: host client
 * @fp: poपूर्णांकer to file काष्ठाure
 *
 */
अटल व्योम mei_cl_vtag_हटाओ_by_fp(स्थिर काष्ठा mei_cl *cl,
				     स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_vtag *vtag_l, *next;

	list_क्रम_each_entry_safe(vtag_l, next, &cl->vtag_map, list) अणु
		अगर (vtag_l->fp == fp) अणु
			list_del(&vtag_l->list);
			kमुक्त(vtag_l);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mei_release - the release function
 *
 * @inode: poपूर्णांकer to inode काष्ठाure
 * @file: poपूर्णांकer to file काष्ठाure
 *
 * Return: 0 on success, <0 on error
 */
अटल पूर्णांक mei_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mei_cl *cl = file->निजी_data;
	काष्ठा mei_device *dev;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	mutex_lock(&dev->device_lock);

	mei_cl_vtag_हटाओ_by_fp(cl, file);

	अगर (!list_empty(&cl->vtag_map)) अणु
		cl_dbg(dev, cl, "not the last vtag\n");
		mei_cl_flush_queues(cl, file);
		rets = 0;
		जाओ out;
	पूर्ण

	rets = mei_cl_disconnect(cl);
	/*
	 * Check again: This is necessary since disconnect releases the lock
	 * and another client can connect in the meanसमय.
	 */
	अगर (!list_empty(&cl->vtag_map)) अणु
		cl_dbg(dev, cl, "not the last vtag after disconnect\n");
		mei_cl_flush_queues(cl, file);
		जाओ out;
	पूर्ण

	mei_cl_flush_queues(cl, शून्य);
	cl_dbg(dev, cl, "removing\n");

	mei_cl_unlink(cl);
	kमुक्त(cl);

out:
	file->निजी_data = शून्य;

	mutex_unlock(&dev->device_lock);
	वापस rets;
पूर्ण


/**
 * mei_पढ़ो - the पढ़ो function.
 *
 * @file: poपूर्णांकer to file काष्ठाure
 * @ubuf: poपूर्णांकer to user buffer
 * @length: buffer length
 * @offset: data offset in buffer
 *
 * Return: >=0 data length on success , <0 on error
 */
अटल sमाप_प्रकार mei_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
			माप_प्रकार length, loff_t *offset)
अणु
	काष्ठा mei_cl *cl = file->निजी_data;
	काष्ठा mei_device *dev;
	काष्ठा mei_cl_cb *cb = शून्य;
	bool nonblock = !!(file->f_flags & O_NONBLOCK);
	sमाप_प्रकार rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;


	mutex_lock(&dev->device_lock);
	अगर (dev->dev_state != MEI_DEV_ENABLED) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (length == 0) अणु
		rets = 0;
		जाओ out;
	पूर्ण

	अगर (ubuf == शून्य) अणु
		rets = -EMSGSIZE;
		जाओ out;
	पूर्ण

	cb = mei_cl_पढ़ो_cb(cl, file);
	अगर (cb)
		जाओ copy_buffer;

	अगर (*offset > 0)
		*offset = 0;

	rets = mei_cl_पढ़ो_start(cl, length, file);
	अगर (rets && rets != -EBUSY) अणु
		cl_dbg(dev, cl, "mei start read failure status = %zd\n", rets);
		जाओ out;
	पूर्ण

	अगर (nonblock) अणु
		rets = -EAGAIN;
		जाओ out;
	पूर्ण

	mutex_unlock(&dev->device_lock);
	अगर (रुको_event_पूर्णांकerruptible(cl->rx_रुको,
				     mei_cl_पढ़ो_cb(cl, file) ||
				     !mei_cl_is_connected(cl))) अणु
		अगर (संकेत_pending(current))
			वापस -EINTR;
		वापस -ERESTARTSYS;
	पूर्ण
	mutex_lock(&dev->device_lock);

	अगर (!mei_cl_is_connected(cl)) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	cb = mei_cl_पढ़ो_cb(cl, file);
	अगर (!cb) अणु
		rets = 0;
		जाओ out;
	पूर्ण

copy_buffer:
	/* now copy the data to user space */
	अगर (cb->status) अणु
		rets = cb->status;
		cl_dbg(dev, cl, "read operation failed %zd\n", rets);
		जाओ मुक्त;
	पूर्ण

	cl_dbg(dev, cl, "buf.size = %zu buf.idx = %zu offset = %lld\n",
	       cb->buf.size, cb->buf_idx, *offset);
	अगर (*offset >= cb->buf_idx) अणु
		rets = 0;
		जाओ मुक्त;
	पूर्ण

	/* length is being truncated to PAGE_SIZE,
	 * however buf_idx may poपूर्णांक beyond that */
	length = min_t(माप_प्रकार, length, cb->buf_idx - *offset);

	अगर (copy_to_user(ubuf, cb->buf.data + *offset, length)) अणु
		dev_dbg(dev->dev, "failed to copy data to userland\n");
		rets = -EFAULT;
		जाओ मुक्त;
	पूर्ण

	rets = length;
	*offset += length;
	/* not all data was पढ़ो, keep the cb */
	अगर (*offset < cb->buf_idx)
		जाओ out;

मुक्त:
	mei_cl_del_rd_completed(cl, cb);
	*offset = 0;

out:
	cl_dbg(dev, cl, "end mei read rets = %zd\n", rets);
	mutex_unlock(&dev->device_lock);
	वापस rets;
पूर्ण

/**
 * mei_cl_vtag_by_fp - obtain the vtag by file poपूर्णांकer
 *
 * @cl: host client
 * @fp: poपूर्णांकer to file काष्ठाure
 *
 * Return: vtag value on success, otherwise 0
 */
अटल u8 mei_cl_vtag_by_fp(स्थिर काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_vtag *cl_vtag;

	अगर (!fp)
		वापस 0;

	list_क्रम_each_entry(cl_vtag, &cl->vtag_map, list)
		अगर (cl_vtag->fp == fp)
			वापस cl_vtag->vtag;
	वापस 0;
पूर्ण

/**
 * mei_ग_लिखो - the ग_लिखो function.
 *
 * @file: poपूर्णांकer to file काष्ठाure
 * @ubuf: poपूर्णांकer to user buffer
 * @length: buffer length
 * @offset: data offset in buffer
 *
 * Return: >=0 data length on success , <0 on error
 */
अटल sमाप_प्रकार mei_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			 माप_प्रकार length, loff_t *offset)
अणु
	काष्ठा mei_cl *cl = file->निजी_data;
	काष्ठा mei_cl_cb *cb;
	काष्ठा mei_device *dev;
	sमाप_प्रकार rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	mutex_lock(&dev->device_lock);

	अगर (dev->dev_state != MEI_DEV_ENABLED) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!mei_cl_is_connected(cl)) अणु
		cl_err(dev, cl, "is not connected");
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!mei_me_cl_is_active(cl->me_cl)) अणु
		rets = -ENOTTY;
		जाओ out;
	पूर्ण

	अगर (length > mei_cl_mtu(cl)) अणु
		rets = -EFBIG;
		जाओ out;
	पूर्ण

	अगर (length == 0) अणु
		rets = 0;
		जाओ out;
	पूर्ण

	जबतक (cl->tx_cb_queued >= dev->tx_queue_limit) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			rets = -EAGAIN;
			जाओ out;
		पूर्ण
		mutex_unlock(&dev->device_lock);
		rets = रुको_event_पूर्णांकerruptible(cl->tx_रुको,
				cl->writing_state == MEI_WRITE_COMPLETE ||
				(!mei_cl_is_connected(cl)));
		mutex_lock(&dev->device_lock);
		अगर (rets) अणु
			अगर (संकेत_pending(current))
				rets = -EINTR;
			जाओ out;
		पूर्ण
		अगर (!mei_cl_is_connected(cl)) अणु
			rets = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण

	cb = mei_cl_alloc_cb(cl, length, MEI_FOP_WRITE, file);
	अगर (!cb) अणु
		rets = -ENOMEM;
		जाओ out;
	पूर्ण
	cb->vtag = mei_cl_vtag_by_fp(cl, file);

	rets = copy_from_user(cb->buf.data, ubuf, length);
	अगर (rets) अणु
		dev_dbg(dev->dev, "failed to copy data from userland\n");
		rets = -EFAULT;
		mei_io_cb_मुक्त(cb);
		जाओ out;
	पूर्ण

	rets = mei_cl_ग_लिखो(cl, cb);
out:
	mutex_unlock(&dev->device_lock);
	वापस rets;
पूर्ण

/**
 * mei_ioctl_connect_client - the connect to fw client IOCTL function
 *
 * @file: निजी data of the file object
 * @in_client_uuid: requested UUID क्रम connection
 * @client: IOCTL connect data, output parameters
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: 0 on success, <0 on failure.
 */
अटल पूर्णांक mei_ioctl_connect_client(काष्ठा file *file,
				    स्थिर uuid_le *in_client_uuid,
				    काष्ठा mei_client *client)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_me_client *me_cl;
	काष्ठा mei_cl *cl;
	पूर्णांक rets;

	cl = file->निजी_data;
	dev = cl->dev;

	अगर (cl->state != MEI_खाता_INITIALIZING &&
	    cl->state != MEI_खाता_DISCONNECTED)
		वापस  -EBUSY;

	/* find ME client we're trying to connect to */
	me_cl = mei_me_cl_by_uuid(dev, in_client_uuid);
	अगर (!me_cl) अणु
		dev_dbg(dev->dev, "Cannot connect to FW Client UUID = %pUl\n",
			in_client_uuid);
		rets = -ENOTTY;
		जाओ end;
	पूर्ण

	अगर (me_cl->props.fixed_address) अणु
		bool क्रमbidden = dev->override_fixed_address ?
			 !dev->allow_fixed_address : !dev->hbm_f_fa_supported;
		अगर (क्रमbidden) अणु
			dev_dbg(dev->dev, "Connection forbidden to FW Client UUID = %pUl\n",
				in_client_uuid);
			rets = -ENOTTY;
			जाओ end;
		पूर्ण
	पूर्ण

	dev_dbg(dev->dev, "Connect to FW Client ID = %d\n",
			me_cl->client_id);
	dev_dbg(dev->dev, "FW Client - Protocol Version = %d\n",
			me_cl->props.protocol_version);
	dev_dbg(dev->dev, "FW Client - Max Msg Len = %d\n",
			me_cl->props.max_msg_length);

	/* prepare the output buffer */
	client->max_msg_length = me_cl->props.max_msg_length;
	client->protocol_version = me_cl->props.protocol_version;
	dev_dbg(dev->dev, "Can connect?\n");

	rets = mei_cl_connect(cl, me_cl, file);

end:
	mei_me_cl_put(me_cl);
	वापस rets;
पूर्ण

/**
 * mei_vt_support_check - check अगर client support vtags
 *
 * Locking: called under "dev->device_lock" lock
 *
 * @dev: mei_device
 * @uuid: client UUID
 *
 * Return:
 *	0 - supported
 *	-ENOTTY - no such client
 *	-EOPNOTSUPP - vtags are not supported by client
 */
अटल पूर्णांक mei_vt_support_check(काष्ठा mei_device *dev, स्थिर uuid_le *uuid)
अणु
	काष्ठा mei_me_client *me_cl;
	पूर्णांक ret;

	अगर (!dev->hbm_f_vt_supported)
		वापस -EOPNOTSUPP;

	me_cl = mei_me_cl_by_uuid(dev, uuid);
	अगर (!me_cl) अणु
		dev_dbg(dev->dev, "Cannot connect to FW Client UUID = %pUl\n",
			uuid);
		वापस -ENOTTY;
	पूर्ण
	ret = me_cl->props.vt_supported ? 0 : -EOPNOTSUPP;
	mei_me_cl_put(me_cl);

	वापस ret;
पूर्ण

/**
 * mei_ioctl_connect_vtag - connect to fw client with vtag IOCTL function
 *
 * @file: निजी data of the file object
 * @in_client_uuid: requested UUID क्रम connection
 * @client: IOCTL connect data, output parameters
 * @vtag: vm tag
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: 0 on success, <0 on failure.
 */
अटल पूर्णांक mei_ioctl_connect_vtag(काष्ठा file *file,
				  स्थिर uuid_le *in_client_uuid,
				  काष्ठा mei_client *client,
				  u8 vtag)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl *cl;
	काष्ठा mei_cl *pos;
	काष्ठा mei_cl_vtag *cl_vtag;

	cl = file->निजी_data;
	dev = cl->dev;

	dev_dbg(dev->dev, "FW Client %pUl vtag %d\n", in_client_uuid, vtag);

	चयन (cl->state) अणु
	हाल MEI_खाता_DISCONNECTED:
		अगर (mei_cl_vtag_by_fp(cl, file) != vtag) अणु
			dev_err(dev->dev, "reconnect with different vtag\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल MEI_खाता_INITIALIZING:
		/* malicious connect from another thपढ़ो may push vtag */
		अगर (!IS_ERR(mei_cl_fp_by_vtag(cl, vtag))) अणु
			dev_err(dev->dev, "vtag already filled\n");
			वापस -EINVAL;
		पूर्ण

		list_क्रम_each_entry(pos, &dev->file_list, link) अणु
			अगर (pos == cl)
				जारी;
			अगर (!pos->me_cl)
				जारी;

			/* only search क्रम same UUID */
			अगर (uuid_le_cmp(*mei_cl_uuid(pos), *in_client_uuid))
				जारी;

			/* अगर tag alपढ़ोy exist try another fp */
			अगर (!IS_ERR(mei_cl_fp_by_vtag(pos, vtag)))
				जारी;

			/* replace cl with acquired one */
			dev_dbg(dev->dev, "replacing with existing cl\n");
			mei_cl_unlink(cl);
			kमुक्त(cl);
			file->निजी_data = pos;
			cl = pos;
			अवरोध;
		पूर्ण

		cl_vtag = mei_cl_vtag_alloc(file, vtag);
		अगर (IS_ERR(cl_vtag))
			वापस -ENOMEM;

		list_add_tail(&cl_vtag->list, &cl->vtag_map);
		अवरोध;
	शेष:
		वापस -EBUSY;
	पूर्ण

	जबतक (cl->state != MEI_खाता_INITIALIZING &&
	       cl->state != MEI_खाता_DISCONNECTED &&
	       cl->state != MEI_खाता_CONNECTED) अणु
		mutex_unlock(&dev->device_lock);
		रुको_event_समयout(cl->रुको,
				   (cl->state == MEI_खाता_CONNECTED ||
				    cl->state == MEI_खाता_DISCONNECTED ||
				    cl->state == MEI_खाता_DISCONNECT_REQUIRED ||
				    cl->state == MEI_खाता_DISCONNECT_REPLY),
				   mei_secs_to_jअगरfies(MEI_CL_CONNECT_TIMEOUT));
		mutex_lock(&dev->device_lock);
	पूर्ण

	अगर (!mei_cl_is_connected(cl))
		वापस mei_ioctl_connect_client(file, in_client_uuid, client);

	client->max_msg_length = cl->me_cl->props.max_msg_length;
	client->protocol_version = cl->me_cl->props.protocol_version;

	वापस 0;
पूर्ण

/**
 * mei_ioctl_client_notअगरy_request -
 *     propagate event notअगरication request to client
 *
 * @file: poपूर्णांकer to file काष्ठाure
 * @request: 0 - disable, 1 - enable
 *
 * Return: 0 on success , <0 on error
 */
अटल पूर्णांक mei_ioctl_client_notअगरy_request(स्थिर काष्ठा file *file, u32 request)
अणु
	काष्ठा mei_cl *cl = file->निजी_data;

	अगर (request != MEI_HBM_NOTIFICATION_START &&
	    request != MEI_HBM_NOTIFICATION_STOP)
		वापस -EINVAL;

	वापस mei_cl_notअगरy_request(cl, file, (u8)request);
पूर्ण

/**
 * mei_ioctl_client_notअगरy_get -  रुको क्रम notअगरication request
 *
 * @file: poपूर्णांकer to file काष्ठाure
 * @notअगरy_get: 0 - disable, 1 - enable
 *
 * Return: 0 on success , <0 on error
 */
अटल पूर्णांक mei_ioctl_client_notअगरy_get(स्थिर काष्ठा file *file, u32 *notअगरy_get)
अणु
	काष्ठा mei_cl *cl = file->निजी_data;
	bool notअगरy_ev;
	bool block = (file->f_flags & O_NONBLOCK) == 0;
	पूर्णांक rets;

	rets = mei_cl_notअगरy_get(cl, block, &notअगरy_ev);
	अगर (rets)
		वापस rets;

	*notअगरy_get = notअगरy_ev ? 1 : 0;
	वापस 0;
पूर्ण

/**
 * mei_ioctl - the IOCTL function
 *
 * @file: poपूर्णांकer to file काष्ठाure
 * @cmd: ioctl command
 * @data: poपूर्णांकer to mei message काष्ठाure
 *
 * Return: 0 on success , <0 on error
 */
अटल दीर्घ mei_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ data)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl *cl = file->निजी_data;
	काष्ठा mei_connect_client_data conn;
	काष्ठा mei_connect_client_data_vtag conn_vtag;
	स्थिर uuid_le *cl_uuid;
	काष्ठा mei_client *props;
	u8 vtag;
	u32 notअगरy_get, notअगरy_req;
	पूर्णांक rets;


	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	dev_dbg(dev->dev, "IOCTL cmd = 0x%x", cmd);

	mutex_lock(&dev->device_lock);
	अगर (dev->dev_state != MEI_DEV_ENABLED) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
	हाल IOCTL_MEI_CONNECT_CLIENT:
		dev_dbg(dev->dev, ": IOCTL_MEI_CONNECT_CLIENT.\n");
		अगर (copy_from_user(&conn, (अक्षर __user *)data, माप(conn))) अणु
			dev_dbg(dev->dev, "failed to copy data from userland\n");
			rets = -EFAULT;
			जाओ out;
		पूर्ण
		cl_uuid = &conn.in_client_uuid;
		props = &conn.out_client_properties;
		vtag = 0;

		rets = mei_vt_support_check(dev, cl_uuid);
		अगर (rets == -ENOTTY)
			जाओ out;
		अगर (!rets)
			rets = mei_ioctl_connect_vtag(file, cl_uuid, props,
						      vtag);
		अन्यथा
			rets = mei_ioctl_connect_client(file, cl_uuid, props);
		अगर (rets)
			जाओ out;

		/* अगर all is ok, copying the data back to user. */
		अगर (copy_to_user((अक्षर __user *)data, &conn, माप(conn))) अणु
			dev_dbg(dev->dev, "failed to copy data to userland\n");
			rets = -EFAULT;
			जाओ out;
		पूर्ण

		अवरोध;

	हाल IOCTL_MEI_CONNECT_CLIENT_VTAG:
		dev_dbg(dev->dev, "IOCTL_MEI_CONNECT_CLIENT_VTAG\n");
		अगर (copy_from_user(&conn_vtag, (अक्षर __user *)data,
				   माप(conn_vtag))) अणु
			dev_dbg(dev->dev, "failed to copy data from userland\n");
			rets = -EFAULT;
			जाओ out;
		पूर्ण

		cl_uuid = &conn_vtag.connect.in_client_uuid;
		props = &conn_vtag.out_client_properties;
		vtag = conn_vtag.connect.vtag;

		rets = mei_vt_support_check(dev, cl_uuid);
		अगर (rets == -EOPNOTSUPP)
			dev_dbg(dev->dev, "FW Client %pUl does not support vtags\n",
				cl_uuid);
		अगर (rets)
			जाओ out;

		अगर (!vtag) अणु
			dev_dbg(dev->dev, "vtag can't be zero\n");
			rets = -EINVAL;
			जाओ out;
		पूर्ण

		rets = mei_ioctl_connect_vtag(file, cl_uuid, props, vtag);
		अगर (rets)
			जाओ out;

		/* अगर all is ok, copying the data back to user. */
		अगर (copy_to_user((अक्षर __user *)data, &conn_vtag,
				 माप(conn_vtag))) अणु
			dev_dbg(dev->dev, "failed to copy data to userland\n");
			rets = -EFAULT;
			जाओ out;
		पूर्ण

		अवरोध;

	हाल IOCTL_MEI_NOTIFY_SET:
		dev_dbg(dev->dev, ": IOCTL_MEI_NOTIFY_SET.\n");
		अगर (copy_from_user(&notअगरy_req,
				   (अक्षर __user *)data, माप(notअगरy_req))) अणु
			dev_dbg(dev->dev, "failed to copy data from userland\n");
			rets = -EFAULT;
			जाओ out;
		पूर्ण
		rets = mei_ioctl_client_notअगरy_request(file, notअगरy_req);
		अवरोध;

	हाल IOCTL_MEI_NOTIFY_GET:
		dev_dbg(dev->dev, ": IOCTL_MEI_NOTIFY_GET.\n");
		rets = mei_ioctl_client_notअगरy_get(file, &notअगरy_get);
		अगर (rets)
			जाओ out;

		dev_dbg(dev->dev, "copy connect data to user\n");
		अगर (copy_to_user((अक्षर __user *)data,
				&notअगरy_get, माप(notअगरy_get))) अणु
			dev_dbg(dev->dev, "failed to copy data to userland\n");
			rets = -EFAULT;
			जाओ out;

		पूर्ण
		अवरोध;

	शेष:
		rets = -ENOIOCTLCMD;
	पूर्ण

out:
	mutex_unlock(&dev->device_lock);
	वापस rets;
पूर्ण

/**
 * mei_poll - the poll function
 *
 * @file: poपूर्णांकer to file काष्ठाure
 * @रुको: poपूर्णांकer to poll_table काष्ठाure
 *
 * Return: poll mask
 */
अटल __poll_t mei_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा mei_cl *cl = file->निजी_data;
	काष्ठा mei_device *dev;
	__poll_t mask = 0;
	bool notअगरy_en;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस EPOLLERR;

	dev = cl->dev;

	mutex_lock(&dev->device_lock);

	notअगरy_en = cl->notअगरy_en && (req_events & EPOLLPRI);

	अगर (dev->dev_state != MEI_DEV_ENABLED ||
	    !mei_cl_is_connected(cl)) अणु
		mask = EPOLLERR;
		जाओ out;
	पूर्ण

	अगर (notअगरy_en) अणु
		poll_रुको(file, &cl->ev_रुको, रुको);
		अगर (cl->notअगरy_ev)
			mask |= EPOLLPRI;
	पूर्ण

	अगर (req_events & (EPOLLIN | EPOLLRDNORM)) अणु
		poll_रुको(file, &cl->rx_रुको, रुको);

		अगर (mei_cl_पढ़ो_cb(cl, file))
			mask |= EPOLLIN | EPOLLRDNORM;
		अन्यथा
			mei_cl_पढ़ो_start(cl, mei_cl_mtu(cl), file);
	पूर्ण

	अगर (req_events & (EPOLLOUT | EPOLLWRNORM)) अणु
		poll_रुको(file, &cl->tx_रुको, रुको);
		अगर (cl->tx_cb_queued < dev->tx_queue_limit)
			mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण

out:
	mutex_unlock(&dev->device_lock);
	वापस mask;
पूर्ण

/**
 * mei_cl_is_ग_लिखो_queued - check अगर the client has pending ग_लिखोs.
 *
 * @cl: writing host client
 *
 * Return: true अगर client is writing, false otherwise.
 */
अटल bool mei_cl_is_ग_लिखो_queued(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev = cl->dev;
	काष्ठा mei_cl_cb *cb;

	list_क्रम_each_entry(cb, &dev->ग_लिखो_list, list)
		अगर (cb->cl == cl)
			वापस true;
	list_क्रम_each_entry(cb, &dev->ग_लिखो_रुकोing_list, list)
		अगर (cb->cl == cl)
			वापस true;
	वापस false;
पूर्ण

/**
 * mei_fsync - the fsync handler
 *
 * @fp:       poपूर्णांकer to file काष्ठाure
 * @start:    unused
 * @end:      unused
 * @datasync: unused
 *
 * Return: 0 on success, -ENODEV अगर client is not connected
 */
अटल पूर्णांक mei_fsync(काष्ठा file *fp, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा mei_cl *cl = fp->निजी_data;
	काष्ठा mei_device *dev;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	mutex_lock(&dev->device_lock);

	अगर (dev->dev_state != MEI_DEV_ENABLED || !mei_cl_is_connected(cl)) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	जबतक (mei_cl_is_ग_लिखो_queued(cl)) अणु
		mutex_unlock(&dev->device_lock);
		rets = रुको_event_पूर्णांकerruptible(cl->tx_रुको,
				cl->writing_state == MEI_WRITE_COMPLETE ||
				!mei_cl_is_connected(cl));
		mutex_lock(&dev->device_lock);
		अगर (rets) अणु
			अगर (संकेत_pending(current))
				rets = -EINTR;
			जाओ out;
		पूर्ण
		अगर (!mei_cl_is_connected(cl)) अणु
			rets = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण
	rets = 0;
out:
	mutex_unlock(&dev->device_lock);
	वापस rets;
पूर्ण

/**
 * mei_fasync - asynchronous io support
 *
 * @fd: file descriptor
 * @file: poपूर्णांकer to file काष्ठाure
 * @band: band biपंचांगap
 *
 * Return: negative on error,
 *         0 अगर it did no changes,
 *         and positive a process was added or deleted
 */
अटल पूर्णांक mei_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक band)
अणु

	काष्ठा mei_cl *cl = file->निजी_data;

	अगर (!mei_cl_is_connected(cl))
		वापस -ENODEV;

	वापस fasync_helper(fd, file, band, &cl->ev_async);
पूर्ण

/**
 * trc_show - mei device trc attribute show method
 *
 * @device: device poपूर्णांकer
 * @attr: attribute poपूर्णांकer
 * @buf:  अक्षर out buffer
 *
 * Return: number of the bytes prपूर्णांकed पूर्णांकo buf or error
 */
अटल sमाप_प्रकार trc_show(काष्ठा device *device,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mei_device *dev = dev_get_drvdata(device);
	u32 trc;
	पूर्णांक ret;

	ret = mei_trc_status(dev, &trc);
	अगर (ret)
		वापस ret;
	वापस प्र_लिखो(buf, "%08X\n", trc);
पूर्ण
अटल DEVICE_ATTR_RO(trc);

/**
 * fw_status_show - mei device fw_status attribute show method
 *
 * @device: device poपूर्णांकer
 * @attr: attribute poपूर्णांकer
 * @buf:  अक्षर out buffer
 *
 * Return: number of the bytes prपूर्णांकed पूर्णांकo buf or error
 */
अटल sमाप_प्रकार fw_status_show(काष्ठा device *device,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mei_device *dev = dev_get_drvdata(device);
	काष्ठा mei_fw_status fw_status;
	पूर्णांक err, i;
	sमाप_प्रकार cnt = 0;

	mutex_lock(&dev->device_lock);
	err = mei_fw_status(dev, &fw_status);
	mutex_unlock(&dev->device_lock);
	अगर (err) अणु
		dev_err(device, "read fw_status error = %d\n", err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < fw_status.count; i++)
		cnt += scnम_लिखो(buf + cnt, PAGE_SIZE - cnt, "%08X\n",
				fw_status.status[i]);
	वापस cnt;
पूर्ण
अटल DEVICE_ATTR_RO(fw_status);

/**
 * hbm_ver_show - display HBM protocol version negotiated with FW
 *
 * @device: device poपूर्णांकer
 * @attr: attribute poपूर्णांकer
 * @buf:  अक्षर out buffer
 *
 * Return: number of the bytes prपूर्णांकed पूर्णांकo buf or error
 */
अटल sमाप_प्रकार hbm_ver_show(काष्ठा device *device,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mei_device *dev = dev_get_drvdata(device);
	काष्ठा hbm_version ver;

	mutex_lock(&dev->device_lock);
	ver = dev->version;
	mutex_unlock(&dev->device_lock);

	वापस प्र_लिखो(buf, "%u.%u\n", ver.major_version, ver.minor_version);
पूर्ण
अटल DEVICE_ATTR_RO(hbm_ver);

/**
 * hbm_ver_drv_show - display HBM protocol version advertised by driver
 *
 * @device: device poपूर्णांकer
 * @attr: attribute poपूर्णांकer
 * @buf:  अक्षर out buffer
 *
 * Return: number of the bytes prपूर्णांकed पूर्णांकo buf or error
 */
अटल sमाप_प्रकार hbm_ver_drv_show(काष्ठा device *device,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u.%u\n", HBM_MAJOR_VERSION, HBM_MINOR_VERSION);
पूर्ण
अटल DEVICE_ATTR_RO(hbm_ver_drv);

अटल sमाप_प्रकार tx_queue_limit_show(काष्ठा device *device,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mei_device *dev = dev_get_drvdata(device);
	u8 size = 0;

	mutex_lock(&dev->device_lock);
	size = dev->tx_queue_limit;
	mutex_unlock(&dev->device_lock);

	वापस sysfs_emit(buf, "%u\n", size);
पूर्ण

अटल sमाप_प्रकार tx_queue_limit_store(काष्ठा device *device,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mei_device *dev = dev_get_drvdata(device);
	u8 limit;
	अचिन्हित पूर्णांक inp;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &inp);
	अगर (err)
		वापस err;
	अगर (inp > MEI_TX_QUEUE_LIMIT_MAX || inp < MEI_TX_QUEUE_LIMIT_MIN)
		वापस -EINVAL;
	limit = inp;

	mutex_lock(&dev->device_lock);
	dev->tx_queue_limit = limit;
	mutex_unlock(&dev->device_lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(tx_queue_limit);

/**
 * fw_ver_show - display ME FW version
 *
 * @device: device poपूर्णांकer
 * @attr: attribute poपूर्णांकer
 * @buf:  अक्षर out buffer
 *
 * Return: number of the bytes prपूर्णांकed पूर्णांकo buf or error
 */
अटल sमाप_प्रकार fw_ver_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mei_device *dev = dev_get_drvdata(device);
	काष्ठा mei_fw_version *ver;
	sमाप_प्रकार cnt = 0;
	पूर्णांक i;

	ver = dev->fw_ver;

	क्रम (i = 0; i < MEI_MAX_FW_VER_BLOCKS; i++)
		cnt += scnम_लिखो(buf + cnt, PAGE_SIZE - cnt, "%u:%u.%u.%u.%u\n",
				 ver[i].platक्रमm, ver[i].major, ver[i].minor,
				 ver[i].hotfix, ver[i].buildno);
	वापस cnt;
पूर्ण
अटल DEVICE_ATTR_RO(fw_ver);

/**
 * dev_state_show - display device state
 *
 * @device: device poपूर्णांकer
 * @attr: attribute poपूर्णांकer
 * @buf:  अक्षर out buffer
 *
 * Return: number of the bytes prपूर्णांकed पूर्णांकo buf or error
 */
अटल sमाप_प्रकार dev_state_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mei_device *dev = dev_get_drvdata(device);
	क्रमागत mei_dev_state dev_state;

	mutex_lock(&dev->device_lock);
	dev_state = dev->dev_state;
	mutex_unlock(&dev->device_lock);

	वापस प्र_लिखो(buf, "%s", mei_dev_state_str(dev_state));
पूर्ण
अटल DEVICE_ATTR_RO(dev_state);

/**
 * dev_set_devstate: set to new device state and notअगरy sysfs file.
 *
 * @dev: mei_device
 * @state: new device state
 */
व्योम mei_set_devstate(काष्ठा mei_device *dev, क्रमागत mei_dev_state state)
अणु
	काष्ठा device *clsdev;

	अगर (dev->dev_state == state)
		वापस;

	dev->dev_state = state;

	clsdev = class_find_device_by_devt(mei_class, dev->cdev.dev);
	अगर (clsdev) अणु
		sysfs_notअगरy(&clsdev->kobj, शून्य, "dev_state");
		put_device(clsdev);
	पूर्ण
पूर्ण

/**
 * kind_show - display device kind
 *
 * @device: device poपूर्णांकer
 * @attr: attribute poपूर्णांकer
 * @buf: अक्षर out buffer
 *
 * Return: number of the bytes prपूर्णांकed पूर्णांकo buf or error
 */
अटल sमाप_प्रकार kind_show(काष्ठा device *device,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mei_device *dev = dev_get_drvdata(device);
	sमाप_प्रकार ret;

	अगर (dev->kind)
		ret = प्र_लिखो(buf, "%s\n", dev->kind);
	अन्यथा
		ret = प्र_लिखो(buf, "%s\n", "mei");

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(kind);

अटल काष्ठा attribute *mei_attrs[] = अणु
	&dev_attr_fw_status.attr,
	&dev_attr_hbm_ver.attr,
	&dev_attr_hbm_ver_drv.attr,
	&dev_attr_tx_queue_limit.attr,
	&dev_attr_fw_ver.attr,
	&dev_attr_dev_state.attr,
	&dev_attr_trc.attr,
	&dev_attr_kind.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(mei);

/*
 * file operations काष्ठाure will be used क्रम mei अक्षर device.
 */
अटल स्थिर काष्ठा file_operations mei_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = mei_पढ़ो,
	.unlocked_ioctl = mei_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो = mei_खोलो,
	.release = mei_release,
	.ग_लिखो = mei_ग_लिखो,
	.poll = mei_poll,
	.fsync = mei_fsync,
	.fasync = mei_fasync,
	.llseek = no_llseek
पूर्ण;

/**
 * mei_minor_get - obtain next मुक्त device minor number
 *
 * @dev:  device poपूर्णांकer
 *
 * Return: allocated minor, or -ENOSPC अगर no मुक्त minor left
 */
अटल पूर्णांक mei_minor_get(काष्ठा mei_device *dev)
अणु
	पूर्णांक ret;

	mutex_lock(&mei_minor_lock);
	ret = idr_alloc(&mei_idr, dev, 0, MEI_MAX_DEVS, GFP_KERNEL);
	अगर (ret >= 0)
		dev->minor = ret;
	अन्यथा अगर (ret == -ENOSPC)
		dev_err(dev->dev, "too many mei devices\n");

	mutex_unlock(&mei_minor_lock);
	वापस ret;
पूर्ण

/**
 * mei_minor_मुक्त - mark device minor number as मुक्त
 *
 * @dev:  device poपूर्णांकer
 */
अटल व्योम mei_minor_मुक्त(काष्ठा mei_device *dev)
अणु
	mutex_lock(&mei_minor_lock);
	idr_हटाओ(&mei_idr, dev->minor);
	mutex_unlock(&mei_minor_lock);
पूर्ण

पूर्णांक mei_रेजिस्टर(काष्ठा mei_device *dev, काष्ठा device *parent)
अणु
	काष्ठा device *clsdev; /* class device */
	पूर्णांक ret, devno;

	ret = mei_minor_get(dev);
	अगर (ret < 0)
		वापस ret;

	/* Fill in the data काष्ठाures */
	devno = MKDEV(MAJOR(mei_devt), dev->minor);
	cdev_init(&dev->cdev, &mei_fops);
	dev->cdev.owner = parent->driver->owner;

	/* Add the device */
	ret = cdev_add(&dev->cdev, devno, 1);
	अगर (ret) अणु
		dev_err(parent, "unable to add device %d:%d\n",
			MAJOR(mei_devt), dev->minor);
		जाओ err_dev_add;
	पूर्ण

	clsdev = device_create_with_groups(mei_class, parent, devno,
					   dev, mei_groups,
					   "mei%d", dev->minor);

	अगर (IS_ERR(clsdev)) अणु
		dev_err(parent, "unable to create device %d:%d\n",
			MAJOR(mei_devt), dev->minor);
		ret = PTR_ERR(clsdev);
		जाओ err_dev_create;
	पूर्ण

	mei_dbgfs_रेजिस्टर(dev, dev_name(clsdev));

	वापस 0;

err_dev_create:
	cdev_del(&dev->cdev);
err_dev_add:
	mei_minor_मुक्त(dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mei_रेजिस्टर);

व्योम mei_deरेजिस्टर(काष्ठा mei_device *dev)
अणु
	पूर्णांक devno;

	devno = dev->cdev.dev;
	cdev_del(&dev->cdev);

	mei_dbgfs_deरेजिस्टर(dev);

	device_destroy(mei_class, devno);

	mei_minor_मुक्त(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mei_deरेजिस्टर);

अटल पूर्णांक __init mei_init(व्योम)
अणु
	पूर्णांक ret;

	mei_class = class_create(THIS_MODULE, "mei");
	अगर (IS_ERR(mei_class)) अणु
		pr_err("couldn't create class\n");
		ret = PTR_ERR(mei_class);
		जाओ err;
	पूर्ण

	ret = alloc_chrdev_region(&mei_devt, 0, MEI_MAX_DEVS, "mei");
	अगर (ret < 0) अणु
		pr_err("unable to allocate char dev region\n");
		जाओ err_class;
	पूर्ण

	ret = mei_cl_bus_init();
	अगर (ret < 0) अणु
		pr_err("unable to initialize bus\n");
		जाओ err_chrdev;
	पूर्ण

	वापस 0;

err_chrdev:
	unरेजिस्टर_chrdev_region(mei_devt, MEI_MAX_DEVS);
err_class:
	class_destroy(mei_class);
err:
	वापस ret;
पूर्ण

अटल व्योम __निकास mei_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(mei_devt, MEI_MAX_DEVS);
	class_destroy(mei_class);
	mei_cl_bus_निकास();
पूर्ण

module_init(mei_init);
module_निकास(mei_निकास);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Intel(R) Management Engine Interface");
MODULE_LICENSE("GPL v2");

