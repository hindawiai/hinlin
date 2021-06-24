<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004 IBM Corporation
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Dave Safक्रमd <safक्रमd@watson.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Copyright (C) 2013 Obsidian Research Corp
 * Jason Gunthorpe <jgunthorpe@obsidianresearch.com>
 *
 * Device file प्रणाली पूर्णांकerface to the TPM
 */
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>
#समावेश "tpm.h"
#समावेश "tpm-dev.h"

अटल काष्ठा workqueue_काष्ठा *tpm_dev_wq;

अटल sमाप_प्रकार tpm_dev_transmit(काष्ठा tpm_chip *chip, काष्ठा tpm_space *space,
				u8 *buf, माप_प्रकार bufsiz)
अणु
	काष्ठा tpm_header *header = (व्योम *)buf;
	sमाप_प्रकार ret, len;

	ret = tpm2_prepare_space(chip, space, buf, bufsiz);
	/* If the command is not implemented by the TPM, synthesize a
	 * response with a TPM2_RC_COMMAND_CODE वापस क्रम user-space.
	 */
	अगर (ret == -EOPNOTSUPP) अणु
		header->length = cpu_to_be32(माप(*header));
		header->tag = cpu_to_be16(TPM2_ST_NO_SESSIONS);
		header->वापस_code = cpu_to_be32(TPM2_RC_COMMAND_CODE |
						  TSS2_RESMGR_TPM_RC_LAYER);
		ret = माप(*header);
	पूर्ण
	अगर (ret)
		जाओ out_rc;

	len = tpm_transmit(chip, buf, bufsiz);
	अगर (len < 0)
		ret = len;

	अगर (!ret)
		ret = tpm2_commit_space(chip, space, buf, &len);

out_rc:
	वापस ret ? ret : len;
पूर्ण

अटल व्योम tpm_dev_async_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा file_priv *priv =
			container_of(work, काष्ठा file_priv, async_work);
	sमाप_प्रकार ret;

	mutex_lock(&priv->buffer_mutex);
	priv->command_enqueued = false;
	ret = tpm_try_get_ops(priv->chip);
	अगर (ret) अणु
		priv->response_length = ret;
		जाओ out;
	पूर्ण

	ret = tpm_dev_transmit(priv->chip, priv->space, priv->data_buffer,
			       माप(priv->data_buffer));
	tpm_put_ops(priv->chip);
	अगर (ret > 0) अणु
		priv->response_length = ret;
		mod_समयr(&priv->user_पढ़ो_समयr, jअगरfies + (120 * HZ));
	पूर्ण
out:
	mutex_unlock(&priv->buffer_mutex);
	wake_up_पूर्णांकerruptible(&priv->async_रुको);
पूर्ण

अटल व्योम user_पढ़ोer_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा file_priv *priv = from_समयr(priv, t, user_पढ़ो_समयr);

	pr_warn("TPM user space timeout is deprecated (pid=%d)\n",
		task_tgid_nr(current));

	schedule_work(&priv->समयout_work);
पूर्ण

अटल व्योम tpm_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा file_priv *priv = container_of(work, काष्ठा file_priv,
					      समयout_work);

	mutex_lock(&priv->buffer_mutex);
	priv->response_पढ़ो = true;
	priv->response_length = 0;
	स_रखो(priv->data_buffer, 0, माप(priv->data_buffer));
	mutex_unlock(&priv->buffer_mutex);
	wake_up_पूर्णांकerruptible(&priv->async_रुको);
पूर्ण

व्योम tpm_common_खोलो(काष्ठा file *file, काष्ठा tpm_chip *chip,
		     काष्ठा file_priv *priv, काष्ठा tpm_space *space)
अणु
	priv->chip = chip;
	priv->space = space;
	priv->response_पढ़ो = true;

	mutex_init(&priv->buffer_mutex);
	समयr_setup(&priv->user_पढ़ो_समयr, user_पढ़ोer_समयout, 0);
	INIT_WORK(&priv->समयout_work, tpm_समयout_work);
	INIT_WORK(&priv->async_work, tpm_dev_async_work);
	init_रुकोqueue_head(&priv->async_रुको);
	file->निजी_data = priv;
पूर्ण

sमाप_प्रकार tpm_common_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार size, loff_t *off)
अणु
	काष्ठा file_priv *priv = file->निजी_data;
	sमाप_प्रकार ret_size = 0;
	पूर्णांक rc;

	mutex_lock(&priv->buffer_mutex);

	अगर (priv->response_length) अणु
		priv->response_पढ़ो = true;

		ret_size = min_t(sमाप_प्रकार, size, priv->response_length);
		अगर (ret_size <= 0) अणु
			priv->response_length = 0;
			जाओ out;
		पूर्ण

		rc = copy_to_user(buf, priv->data_buffer + *off, ret_size);
		अगर (rc) अणु
			स_रखो(priv->data_buffer, 0, TPM_बफ_मानE);
			priv->response_length = 0;
			ret_size = -EFAULT;
		पूर्ण अन्यथा अणु
			स_रखो(priv->data_buffer + *off, 0, ret_size);
			priv->response_length -= ret_size;
			*off += ret_size;
		पूर्ण
	पूर्ण

out:
	अगर (!priv->response_length) अणु
		*off = 0;
		del_singleshot_समयr_sync(&priv->user_पढ़ो_समयr);
		flush_work(&priv->समयout_work);
	पूर्ण
	mutex_unlock(&priv->buffer_mutex);
	वापस ret_size;
पूर्ण

sमाप_प्रकार tpm_common_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार size, loff_t *off)
अणु
	काष्ठा file_priv *priv = file->निजी_data;
	पूर्णांक ret = 0;

	अगर (size > TPM_बफ_मानE)
		वापस -E2BIG;

	mutex_lock(&priv->buffer_mutex);

	/* Cannot perक्रमm a ग_लिखो until the पढ़ो has cleared either via
	 * tpm_पढ़ो or a user_पढ़ो_समयr समयout. This also prevents split
	 * buffered ग_लिखोs from blocking here.
	 */
	अगर ((!priv->response_पढ़ो && priv->response_length) ||
	    priv->command_enqueued) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(priv->data_buffer, buf, size)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (size < 6 ||
	    size < be32_to_cpu(*((__be32 *)(priv->data_buffer + 2)))) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	priv->response_length = 0;
	priv->response_पढ़ो = false;
	*off = 0;

	/*
	 * If in nonblocking mode schedule an async job to send
	 * the command वापस the size.
	 * In हाल of error the err code will be वापसed in
	 * the subsequent पढ़ो call.
	 */
	अगर (file->f_flags & O_NONBLOCK) अणु
		priv->command_enqueued = true;
		queue_work(tpm_dev_wq, &priv->async_work);
		mutex_unlock(&priv->buffer_mutex);
		वापस size;
	पूर्ण

	/* atomic tpm command send and result receive. We only hold the ops
	 * lock during this period so that the tpm can be unरेजिस्टरed even अगर
	 * the अक्षर dev is held खोलो.
	 */
	अगर (tpm_try_get_ops(priv->chip)) अणु
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	ret = tpm_dev_transmit(priv->chip, priv->space, priv->data_buffer,
			       माप(priv->data_buffer));
	tpm_put_ops(priv->chip);

	अगर (ret > 0) अणु
		priv->response_length = ret;
		mod_समयr(&priv->user_पढ़ो_समयr, jअगरfies + (120 * HZ));
		ret = size;
	पूर्ण
out:
	mutex_unlock(&priv->buffer_mutex);
	वापस ret;
पूर्ण

__poll_t tpm_common_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा file_priv *priv = file->निजी_data;
	__poll_t mask = 0;

	poll_रुको(file, &priv->async_रुको, रुको);
	mutex_lock(&priv->buffer_mutex);

	/*
	 * The response_length indicates अगर there is still response
	 * (or part of it) to be consumed. Partial पढ़ोs decrease it
	 * by the number of bytes पढ़ो, and ग_लिखो resets it the zero.
	 */
	अगर (priv->response_length)
		mask = EPOLLIN | EPOLLRDNORM;
	अन्यथा
		mask = EPOLLOUT | EPOLLWRNORM;

	mutex_unlock(&priv->buffer_mutex);
	वापस mask;
पूर्ण

/*
 * Called on file बंद
 */
व्योम tpm_common_release(काष्ठा file *file, काष्ठा file_priv *priv)
अणु
	flush_work(&priv->async_work);
	del_singleshot_समयr_sync(&priv->user_पढ़ो_समयr);
	flush_work(&priv->समयout_work);
	file->निजी_data = शून्य;
	priv->response_length = 0;
पूर्ण

पूर्णांक __init tpm_dev_common_init(व्योम)
अणु
	tpm_dev_wq = alloc_workqueue("tpm_dev_wq", WQ_MEM_RECLAIM, 0);

	वापस !tpm_dev_wq ? -ENOMEM : 0;
पूर्ण

व्योम __निकास tpm_dev_common_निकास(व्योम)
अणु
	अगर (tpm_dev_wq) अणु
		destroy_workqueue(tpm_dev_wq);
		tpm_dev_wq = शून्य;
	पूर्ण
पूर्ण
