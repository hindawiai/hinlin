<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 2008 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mhalcrow@us.ibm.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/hash.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश "ecryptfs_kernel.h"

अटल atomic_t ecryptfs_num_miscdev_खोलोs;

/**
 * ecryptfs_miscdev_poll
 * @file: dev file
 * @pt: dev poll table (ignored)
 *
 * Returns the poll mask
 */
अटल __poll_t
ecryptfs_miscdev_poll(काष्ठा file *file, poll_table *pt)
अणु
	काष्ठा ecryptfs_daemon *daemon = file->निजी_data;
	__poll_t mask = 0;

	mutex_lock(&daemon->mux);
	अगर (daemon->flags & ECRYPTFS_DAEMON_ZOMBIE) अणु
		prपूर्णांकk(KERN_WARNING "%s: Attempt to poll on zombified "
		       "daemon\n", __func__);
		जाओ out_unlock_daemon;
	पूर्ण
	अगर (daemon->flags & ECRYPTFS_DAEMON_IN_READ)
		जाओ out_unlock_daemon;
	अगर (daemon->flags & ECRYPTFS_DAEMON_IN_POLL)
		जाओ out_unlock_daemon;
	daemon->flags |= ECRYPTFS_DAEMON_IN_POLL;
	mutex_unlock(&daemon->mux);
	poll_रुको(file, &daemon->रुको, pt);
	mutex_lock(&daemon->mux);
	अगर (!list_empty(&daemon->msg_ctx_out_queue))
		mask |= EPOLLIN | EPOLLRDNORM;
out_unlock_daemon:
	daemon->flags &= ~ECRYPTFS_DAEMON_IN_POLL;
	mutex_unlock(&daemon->mux);
	वापस mask;
पूर्ण

/**
 * ecryptfs_miscdev_खोलो
 * @inode: inode of miscdev handle (ignored)
 * @file: file क्रम miscdev handle
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक
ecryptfs_miscdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ecryptfs_daemon *daemon = शून्य;
	पूर्णांक rc;

	mutex_lock(&ecryptfs_daemon_hash_mux);
	rc = ecryptfs_find_daemon_by_euid(&daemon);
	अगर (!rc) अणु
		rc = -EINVAL;
		जाओ out_unlock_daemon_list;
	पूर्ण
	rc = ecryptfs_spawn_daemon(&daemon, file);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to spawn daemon; "
		       "rc = [%d]\n", __func__, rc);
		जाओ out_unlock_daemon_list;
	पूर्ण
	mutex_lock(&daemon->mux);
	अगर (daemon->flags & ECRYPTFS_DAEMON_MISCDEV_OPEN) अणु
		rc = -EBUSY;
		जाओ out_unlock_daemon;
	पूर्ण
	daemon->flags |= ECRYPTFS_DAEMON_MISCDEV_OPEN;
	file->निजी_data = daemon;
	atomic_inc(&ecryptfs_num_miscdev_खोलोs);
out_unlock_daemon:
	mutex_unlock(&daemon->mux);
out_unlock_daemon_list:
	mutex_unlock(&ecryptfs_daemon_hash_mux);
	वापस rc;
पूर्ण

/**
 * ecryptfs_miscdev_release
 * @inode: inode of fs/ecryptfs/euid handle (ignored)
 * @file: file क्रम fs/ecryptfs/euid handle
 *
 * This keeps the daemon रेजिस्टरed until the daemon sends another
 * ioctl to fs/ecryptfs/ctl or until the kernel module unरेजिस्टरs.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक
ecryptfs_miscdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ecryptfs_daemon *daemon = file->निजी_data;
	पूर्णांक rc;

	mutex_lock(&daemon->mux);
	BUG_ON(!(daemon->flags & ECRYPTFS_DAEMON_MISCDEV_OPEN));
	daemon->flags &= ~ECRYPTFS_DAEMON_MISCDEV_OPEN;
	atomic_dec(&ecryptfs_num_miscdev_खोलोs);
	mutex_unlock(&daemon->mux);

	mutex_lock(&ecryptfs_daemon_hash_mux);
	rc = ecryptfs_exorcise_daemon(daemon);
	mutex_unlock(&ecryptfs_daemon_hash_mux);
	अगर (rc) अणु
		prपूर्णांकk(KERN_CRIT "%s: Fatal error whilst attempting to "
		       "shut down daemon; rc = [%d]. Please report this "
		       "bug.\n", __func__, rc);
		BUG();
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ecryptfs_send_miscdev
 * @data: Data to send to daemon; may be शून्य
 * @data_size: Amount of data to send to daemon
 * @msg_ctx: Message context, which is used to handle the reply. If
 *           this is शून्य, then we करो not expect a reply.
 * @msg_type: Type of message
 * @msg_flags: Flags क्रम message
 * @daemon: eCryptfs daemon object
 *
 * Add msg_ctx to queue and then, अगर it exists, notअगरy the blocked
 * miscdevess about the data being available. Must be called with
 * ecryptfs_daemon_hash_mux held.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_send_miscdev(अक्षर *data, माप_प्रकार data_size,
			  काष्ठा ecryptfs_msg_ctx *msg_ctx, u8 msg_type,
			  u16 msg_flags, काष्ठा ecryptfs_daemon *daemon)
अणु
	काष्ठा ecryptfs_message *msg;

	msg = kदो_स्मृति((माप(*msg) + data_size), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	mutex_lock(&msg_ctx->mux);
	msg_ctx->msg = msg;
	msg_ctx->msg->index = msg_ctx->index;
	msg_ctx->msg->data_len = data_size;
	msg_ctx->type = msg_type;
	स_नकल(msg_ctx->msg->data, data, data_size);
	msg_ctx->msg_size = (माप(*msg_ctx->msg) + data_size);
	list_add_tail(&msg_ctx->daemon_out_list, &daemon->msg_ctx_out_queue);
	mutex_unlock(&msg_ctx->mux);

	mutex_lock(&daemon->mux);
	daemon->num_queued_msg_ctx++;
	wake_up_पूर्णांकerruptible(&daemon->रुको);
	mutex_unlock(&daemon->mux);

	वापस 0;
पूर्ण

/*
 * miscdevfs packet क्रमmat:
 *  Octet 0: Type
 *  Octets 1-4: network byte order msg_ctx->counter
 *  Octets 5-N0: Size of काष्ठा ecryptfs_message to follow
 *  Octets N0-N1: काष्ठा ecryptfs_message (including data)
 *
 *  Octets 5-N1 not written अगर the packet type करोes not include a message
 */
#घोषणा PKT_TYPE_SIZE		1
#घोषणा PKT_CTR_SIZE		4
#घोषणा MIN_NON_MSG_PKT_SIZE	(PKT_TYPE_SIZE + PKT_CTR_SIZE)
#घोषणा MIN_MSG_PKT_SIZE	(PKT_TYPE_SIZE + PKT_CTR_SIZE \
				 + ECRYPTFS_MIN_PKT_LEN_SIZE)
/* 4 + ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES comes from tag 65 packet क्रमmat */
#घोषणा MAX_MSG_PKT_SIZE	(PKT_TYPE_SIZE + PKT_CTR_SIZE \
				 + ECRYPTFS_MAX_PKT_LEN_SIZE \
				 + माप(काष्ठा ecryptfs_message) \
				 + 4 + ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES)
#घोषणा PKT_TYPE_OFFSET		0
#घोषणा PKT_CTR_OFFSET		PKT_TYPE_SIZE
#घोषणा PKT_LEN_OFFSET		(PKT_TYPE_SIZE + PKT_CTR_SIZE)

/**
 * ecryptfs_miscdev_पढ़ो - क्रमmat and send message from queue
 * @file: miscdevfs handle
 * @buf: User buffer पूर्णांकo which to copy the next message on the daemon queue
 * @count: Amount of space available in @buf
 * @ppos: Offset in file (ignored)
 *
 * Pulls the most recent message from the daemon queue, क्रमmats it क्रम
 * being sent via a miscdevfs handle, and copies it पूर्णांकo @buf
 *
 * Returns the number of bytes copied पूर्णांकo the user buffer
 */
अटल sमाप_प्रकार
ecryptfs_miscdev_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
		      loff_t *ppos)
अणु
	काष्ठा ecryptfs_daemon *daemon = file->निजी_data;
	काष्ठा ecryptfs_msg_ctx *msg_ctx;
	माप_प्रकार packet_length_size;
	अक्षर packet_length[ECRYPTFS_MAX_PKT_LEN_SIZE];
	माप_प्रकार i;
	माप_प्रकार total_length;
	पूर्णांक rc;

	mutex_lock(&daemon->mux);
	अगर (daemon->flags & ECRYPTFS_DAEMON_ZOMBIE) अणु
		rc = 0;
		prपूर्णांकk(KERN_WARNING "%s: Attempt to read from zombified "
		       "daemon\n", __func__);
		जाओ out_unlock_daemon;
	पूर्ण
	अगर (daemon->flags & ECRYPTFS_DAEMON_IN_READ) अणु
		rc = 0;
		जाओ out_unlock_daemon;
	पूर्ण
	/* This daemon will not go away so दीर्घ as this flag is set */
	daemon->flags |= ECRYPTFS_DAEMON_IN_READ;
check_list:
	अगर (list_empty(&daemon->msg_ctx_out_queue)) अणु
		mutex_unlock(&daemon->mux);
		rc = रुको_event_पूर्णांकerruptible(
			daemon->रुको, !list_empty(&daemon->msg_ctx_out_queue));
		mutex_lock(&daemon->mux);
		अगर (rc < 0) अणु
			rc = 0;
			जाओ out_unlock_daemon;
		पूर्ण
	पूर्ण
	अगर (daemon->flags & ECRYPTFS_DAEMON_ZOMBIE) अणु
		rc = 0;
		जाओ out_unlock_daemon;
	पूर्ण
	अगर (list_empty(&daemon->msg_ctx_out_queue)) अणु
		/* Something अन्यथा jumped in since the
		 * रुको_event_पूर्णांकerruptable() and हटाओd the
		 * message from the queue; try again */
		जाओ check_list;
	पूर्ण
	msg_ctx = list_first_entry(&daemon->msg_ctx_out_queue,
				   काष्ठा ecryptfs_msg_ctx, daemon_out_list);
	BUG_ON(!msg_ctx);
	mutex_lock(&msg_ctx->mux);
	अगर (msg_ctx->msg) अणु
		rc = ecryptfs_ग_लिखो_packet_length(packet_length,
						  msg_ctx->msg_size,
						  &packet_length_size);
		अगर (rc) अणु
			rc = 0;
			prपूर्णांकk(KERN_WARNING "%s: Error writing packet length; "
			       "rc = [%d]\n", __func__, rc);
			जाओ out_unlock_msg_ctx;
		पूर्ण
	पूर्ण अन्यथा अणु
		packet_length_size = 0;
		msg_ctx->msg_size = 0;
	पूर्ण
	total_length = (PKT_TYPE_SIZE + PKT_CTR_SIZE + packet_length_size
			+ msg_ctx->msg_size);
	अगर (count < total_length) अणु
		rc = 0;
		prपूर्णांकk(KERN_WARNING "%s: Only given user buffer of "
		       "size [%zd], but we need [%zd] to read the "
		       "pending message\n", __func__, count, total_length);
		जाओ out_unlock_msg_ctx;
	पूर्ण
	rc = -EFAULT;
	अगर (put_user(msg_ctx->type, buf))
		जाओ out_unlock_msg_ctx;
	अगर (put_user(cpu_to_be32(msg_ctx->counter),
		     (__be32 __user *)(&buf[PKT_CTR_OFFSET])))
		जाओ out_unlock_msg_ctx;
	i = PKT_TYPE_SIZE + PKT_CTR_SIZE;
	अगर (msg_ctx->msg) अणु
		अगर (copy_to_user(&buf[i], packet_length, packet_length_size))
			जाओ out_unlock_msg_ctx;
		i += packet_length_size;
		अगर (copy_to_user(&buf[i], msg_ctx->msg, msg_ctx->msg_size))
			जाओ out_unlock_msg_ctx;
		i += msg_ctx->msg_size;
	पूर्ण
	rc = i;
	list_del(&msg_ctx->daemon_out_list);
	kमुक्त(msg_ctx->msg);
	msg_ctx->msg = शून्य;
	/* We करो not expect a reply from the userspace daemon क्रम any
	 * message type other than ECRYPTFS_MSG_REQUEST */
	अगर (msg_ctx->type != ECRYPTFS_MSG_REQUEST)
		ecryptfs_msg_ctx_alloc_to_मुक्त(msg_ctx);
out_unlock_msg_ctx:
	mutex_unlock(&msg_ctx->mux);
out_unlock_daemon:
	daemon->flags &= ~ECRYPTFS_DAEMON_IN_READ;
	mutex_unlock(&daemon->mux);
	वापस rc;
पूर्ण

/**
 * ecryptfs_miscdev_response - miscdevess response to message previously sent to daemon
 * @daemon: eCryptfs daemon object
 * @data: Bytes comprising काष्ठा ecryptfs_message
 * @data_size: माप(काष्ठा ecryptfs_message) + data len
 * @seq: Sequence number क्रम miscdev response packet
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_miscdev_response(काष्ठा ecryptfs_daemon *daemon, अक्षर *data,
				     माप_प्रकार data_size, u32 seq)
अणु
	काष्ठा ecryptfs_message *msg = (काष्ठा ecryptfs_message *)data;
	पूर्णांक rc;

	अगर ((माप(*msg) + msg->data_len) != data_size) अणु
		prपूर्णांकk(KERN_WARNING "%s: (sizeof(*msg) + msg->data_len) = "
		       "[%zd]; data_size = [%zd]. Invalid packet.\n", __func__,
		       (माप(*msg) + msg->data_len), data_size);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	rc = ecryptfs_process_response(daemon, msg, seq);
	अगर (rc)
		prपूर्णांकk(KERN_ERR
		       "Error processing response message; rc = [%d]\n", rc);
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_miscdev_ग_लिखो - handle ग_लिखो to daemon miscdev handle
 * @file: File क्रम misc dev handle
 * @buf: Buffer containing user data
 * @count: Amount of data in @buf
 * @ppos: Poपूर्णांकer to offset in file (ignored)
 *
 * Returns the number of bytes पढ़ो from @buf
 */
अटल sमाप_प्रकार
ecryptfs_miscdev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		       माप_प्रकार count, loff_t *ppos)
अणु
	__be32 counter_nbo;
	u32 seq;
	माप_प्रकार packet_size, packet_size_length;
	अक्षर *data;
	अचिन्हित अक्षर packet_size_peek[ECRYPTFS_MAX_PKT_LEN_SIZE];
	sमाप_प्रकार rc;

	अगर (count == 0) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (count == MIN_NON_MSG_PKT_SIZE) अणु
		/* Likely a harmless MSG_HELO or MSG_QUIT - no packet length */
		जाओ memdup;
	पूर्ण अन्यथा अगर (count < MIN_MSG_PKT_SIZE || count > MAX_MSG_PKT_SIZE) अणु
		prपूर्णांकk(KERN_WARNING "%s: Acceptable packet size range is "
		       "[%d-%zu], but amount of data written is [%zu].\n",
		       __func__, MIN_MSG_PKT_SIZE, MAX_MSG_PKT_SIZE, count);
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(packet_size_peek, &buf[PKT_LEN_OFFSET],
			   माप(packet_size_peek))) अणु
		prपूर्णांकk(KERN_WARNING "%s: Error while inspecting packet size\n",
		       __func__);
		वापस -EFAULT;
	पूर्ण

	rc = ecryptfs_parse_packet_length(packet_size_peek, &packet_size,
					  &packet_size_length);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "%s: Error parsing packet length; "
		       "rc = [%zd]\n", __func__, rc);
		वापस rc;
	पूर्ण

	अगर ((PKT_TYPE_SIZE + PKT_CTR_SIZE + packet_size_length + packet_size)
	    != count) अणु
		prपूर्णांकk(KERN_WARNING "%s: Invalid packet size [%zu]\n", __func__,
		       packet_size);
		वापस -EINVAL;
	पूर्ण

memdup:
	data = memdup_user(buf, count);
	अगर (IS_ERR(data)) अणु
		prपूर्णांकk(KERN_ERR "%s: memdup_user returned error [%ld]\n",
		       __func__, PTR_ERR(data));
		वापस PTR_ERR(data);
	पूर्ण
	चयन (data[PKT_TYPE_OFFSET]) अणु
	हाल ECRYPTFS_MSG_RESPONSE:
		अगर (count < (MIN_MSG_PKT_SIZE
			     + माप(काष्ठा ecryptfs_message))) अणु
			prपूर्णांकk(KERN_WARNING "%s: Minimum acceptable packet "
			       "size is [%zd], but amount of data written is "
			       "only [%zd]. Discarding response packet.\n",
			       __func__,
			       (MIN_MSG_PKT_SIZE
				+ माप(काष्ठा ecryptfs_message)), count);
			rc = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		स_नकल(&counter_nbo, &data[PKT_CTR_OFFSET], PKT_CTR_SIZE);
		seq = be32_to_cpu(counter_nbo);
		rc = ecryptfs_miscdev_response(file->निजी_data,
				&data[PKT_LEN_OFFSET + packet_size_length],
				packet_size, seq);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "%s: Failed to deliver miscdev "
			       "response to requesting operation; rc = [%zd]\n",
			       __func__, rc);
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल ECRYPTFS_MSG_HELO:
	हाल ECRYPTFS_MSG_QUIT:
		अवरोध;
	शेष:
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Dropping miscdev "
				"message of unrecognized type [%d]\n",
				data[0]);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	rc = count;
out_मुक्त:
	kमुक्त(data);
	वापस rc;
पूर्ण


अटल स्थिर काष्ठा file_operations ecryptfs_miscdev_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = ecryptfs_miscdev_खोलो,
	.poll    = ecryptfs_miscdev_poll,
	.पढ़ो    = ecryptfs_miscdev_पढ़ो,
	.ग_लिखो   = ecryptfs_miscdev_ग_लिखो,
	.release = ecryptfs_miscdev_release,
	.llseek  = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice ecryptfs_miscdev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "ecryptfs",
	.fops  = &ecryptfs_miscdev_fops
पूर्ण;

/**
 * ecryptfs_init_ecryptfs_miscdev
 *
 * Messages sent to the userspace daemon from the kernel are placed on
 * a queue associated with the daemon. The next पढ़ो against the
 * miscdev handle by that daemon will वापस the oldest message placed
 * on the message queue क्रम the daemon.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक __init ecryptfs_init_ecryptfs_miscdev(व्योम)
अणु
	पूर्णांक rc;

	atomic_set(&ecryptfs_num_miscdev_खोलोs, 0);
	rc = misc_रेजिस्टर(&ecryptfs_miscdev);
	अगर (rc)
		prपूर्णांकk(KERN_ERR "%s: Failed to register miscellaneous device "
		       "for communications with userspace daemons; rc = [%d]\n",
		       __func__, rc);
	वापस rc;
पूर्ण

/**
 * ecryptfs_destroy_ecryptfs_miscdev
 *
 * All of the daemons must be exorcised prior to calling this
 * function.
 */
व्योम ecryptfs_destroy_ecryptfs_miscdev(व्योम)
अणु
	BUG_ON(atomic_पढ़ो(&ecryptfs_num_miscdev_खोलोs) != 0);
	misc_deरेजिस्टर(&ecryptfs_miscdev);
पूर्ण
