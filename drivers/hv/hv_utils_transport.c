<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel/userspace transport असलtraction क्रम Hyper-V util driver.
 *
 * Copyright (C) 2015, Vitaly Kuznetsov <vkuznets@redhat.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>

#समावेश "hyperv_vmbus.h"
#समावेश "hv_utils_transport.h"

अटल DEFINE_SPINLOCK(hvt_list_lock);
अटल काष्ठा list_head hvt_list = LIST_HEAD_INIT(hvt_list);

अटल व्योम hvt_reset(काष्ठा hvutil_transport *hvt)
अणु
	kमुक्त(hvt->ouपंचांगsg);
	hvt->ouपंचांगsg = शून्य;
	hvt->ouपंचांगsg_len = 0;
	अगर (hvt->on_reset)
		hvt->on_reset();
पूर्ण

अटल sमाप_प्रकार hvt_op_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hvutil_transport *hvt;
	पूर्णांक ret;

	hvt = container_of(file->f_op, काष्ठा hvutil_transport, fops);

	अगर (रुको_event_पूर्णांकerruptible(hvt->ouपंचांगsg_q, hvt->ouपंचांगsg_len > 0 ||
				     hvt->mode != HVUTIL_TRANSPORT_CHARDEV))
		वापस -EINTR;

	mutex_lock(&hvt->lock);

	अगर (hvt->mode == HVUTIL_TRANSPORT_DESTROY) अणु
		ret = -EBADF;
		जाओ out_unlock;
	पूर्ण

	अगर (!hvt->ouपंचांगsg) अणु
		ret = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	अगर (count < hvt->ouपंचांगsg_len) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (!copy_to_user(buf, hvt->ouपंचांगsg, hvt->ouपंचांगsg_len))
		ret = hvt->ouपंचांगsg_len;
	अन्यथा
		ret = -EFAULT;

	kमुक्त(hvt->ouपंचांगsg);
	hvt->ouपंचांगsg = शून्य;
	hvt->ouपंचांगsg_len = 0;

	अगर (hvt->on_पढ़ो)
		hvt->on_पढ़ो();
	hvt->on_पढ़ो = शून्य;

out_unlock:
	mutex_unlock(&hvt->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार hvt_op_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hvutil_transport *hvt;
	u8 *inmsg;
	पूर्णांक ret;

	hvt = container_of(file->f_op, काष्ठा hvutil_transport, fops);

	inmsg = memdup_user(buf, count);
	अगर (IS_ERR(inmsg))
		वापस PTR_ERR(inmsg);

	अगर (hvt->mode == HVUTIL_TRANSPORT_DESTROY)
		ret = -EBADF;
	अन्यथा
		ret = hvt->on_msg(inmsg, count);

	kमुक्त(inmsg);

	वापस ret ? ret : count;
पूर्ण

अटल __poll_t hvt_op_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा hvutil_transport *hvt;

	hvt = container_of(file->f_op, काष्ठा hvutil_transport, fops);

	poll_रुको(file, &hvt->ouपंचांगsg_q, रुको);

	अगर (hvt->mode == HVUTIL_TRANSPORT_DESTROY)
		वापस EPOLLERR | EPOLLHUP;

	अगर (hvt->ouपंचांगsg_len > 0)
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

अटल पूर्णांक hvt_op_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hvutil_transport *hvt;
	पूर्णांक ret = 0;
	bool issue_reset = false;

	hvt = container_of(file->f_op, काष्ठा hvutil_transport, fops);

	mutex_lock(&hvt->lock);

	अगर (hvt->mode == HVUTIL_TRANSPORT_DESTROY) अणु
		ret = -EBADF;
	पूर्ण अन्यथा अगर (hvt->mode == HVUTIL_TRANSPORT_INIT) अणु
		/*
		 * Switching to CHARDEV mode. We चयन bach to INIT when
		 * device माला_लो released.
		 */
		hvt->mode = HVUTIL_TRANSPORT_CHARDEV;
	पूर्ण
	अन्यथा अगर (hvt->mode == HVUTIL_TRANSPORT_NETLINK) अणु
		/*
		 * We're चयनing from netlink communication to using अक्षर
		 * device. Issue the reset first.
		 */
		issue_reset = true;
		hvt->mode = HVUTIL_TRANSPORT_CHARDEV;
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण

	अगर (issue_reset)
		hvt_reset(hvt);

	mutex_unlock(&hvt->lock);

	वापस ret;
पूर्ण

अटल व्योम hvt_transport_मुक्त(काष्ठा hvutil_transport *hvt)
अणु
	misc_deरेजिस्टर(&hvt->mdev);
	kमुक्त(hvt->ouपंचांगsg);
	kमुक्त(hvt);
पूर्ण

अटल पूर्णांक hvt_op_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hvutil_transport *hvt;
	पूर्णांक mode_old;

	hvt = container_of(file->f_op, काष्ठा hvutil_transport, fops);

	mutex_lock(&hvt->lock);
	mode_old = hvt->mode;
	अगर (hvt->mode != HVUTIL_TRANSPORT_DESTROY)
		hvt->mode = HVUTIL_TRANSPORT_INIT;
	/*
	 * Cleanup message buffers to aव्योम spurious messages when the daemon
	 * connects back.
	 */
	hvt_reset(hvt);

	अगर (mode_old == HVUTIL_TRANSPORT_DESTROY)
		complete(&hvt->release);

	mutex_unlock(&hvt->lock);

	वापस 0;
पूर्ण

अटल व्योम hvt_cn_callback(काष्ठा cn_msg *msg, काष्ठा netlink_skb_parms *nsp)
अणु
	काष्ठा hvutil_transport *hvt, *hvt_found = शून्य;

	spin_lock(&hvt_list_lock);
	list_क्रम_each_entry(hvt, &hvt_list, list) अणु
		अगर (hvt->cn_id.idx == msg->id.idx &&
		    hvt->cn_id.val == msg->id.val) अणु
			hvt_found = hvt;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&hvt_list_lock);
	अगर (!hvt_found) अणु
		pr_warn("hvt_cn_callback: spurious message received!\n");
		वापस;
	पूर्ण

	/*
	 * Switching to NETLINK mode. Switching to CHARDEV happens when someone
	 * खोलोs the device.
	 */
	mutex_lock(&hvt->lock);
	अगर (hvt->mode == HVUTIL_TRANSPORT_INIT)
		hvt->mode = HVUTIL_TRANSPORT_NETLINK;

	अगर (hvt->mode == HVUTIL_TRANSPORT_NETLINK)
		hvt_found->on_msg(msg->data, msg->len);
	अन्यथा
		pr_warn("hvt_cn_callback: unexpected netlink message!\n");
	mutex_unlock(&hvt->lock);
पूर्ण

पूर्णांक hvutil_transport_send(काष्ठा hvutil_transport *hvt, व्योम *msg, पूर्णांक len,
			  व्योम (*on_पढ़ो_cb)(व्योम))
अणु
	काष्ठा cn_msg *cn_msg;
	पूर्णांक ret = 0;

	अगर (hvt->mode == HVUTIL_TRANSPORT_INIT ||
	    hvt->mode == HVUTIL_TRANSPORT_DESTROY) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (hvt->mode == HVUTIL_TRANSPORT_NETLINK) अणु
		cn_msg = kzalloc(माप(*cn_msg) + len, GFP_ATOMIC);
		अगर (!cn_msg)
			वापस -ENOMEM;
		cn_msg->id.idx = hvt->cn_id.idx;
		cn_msg->id.val = hvt->cn_id.val;
		cn_msg->len = len;
		स_नकल(cn_msg->data, msg, len);
		ret = cn_netlink_send(cn_msg, 0, 0, GFP_ATOMIC);
		kमुक्त(cn_msg);
		/*
		 * We करोn't know when netlink messages are delivered but unlike
		 * in CHARDEV mode we're not blocked and we can send next
		 * messages right away.
		 */
		अगर (on_पढ़ो_cb)
			on_पढ़ो_cb();
		वापस ret;
	पूर्ण
	/* HVUTIL_TRANSPORT_CHARDEV */
	mutex_lock(&hvt->lock);
	अगर (hvt->mode != HVUTIL_TRANSPORT_CHARDEV) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (hvt->ouपंचांगsg) अणु
		/* Previous message wasn't received */
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण
	hvt->ouपंचांगsg = kzalloc(len, GFP_KERNEL);
	अगर (hvt->ouपंचांगsg) अणु
		स_नकल(hvt->ouपंचांगsg, msg, len);
		hvt->ouपंचांगsg_len = len;
		hvt->on_पढ़ो = on_पढ़ो_cb;
		wake_up_पूर्णांकerruptible(&hvt->ouपंचांगsg_q);
	पूर्ण अन्यथा
		ret = -ENOMEM;
out_unlock:
	mutex_unlock(&hvt->lock);
	वापस ret;
पूर्ण

काष्ठा hvutil_transport *hvutil_transport_init(स्थिर अक्षर *name,
					       u32 cn_idx, u32 cn_val,
					       पूर्णांक (*on_msg)(व्योम *, पूर्णांक),
					       व्योम (*on_reset)(व्योम))
अणु
	काष्ठा hvutil_transport *hvt;

	hvt = kzalloc(माप(*hvt), GFP_KERNEL);
	अगर (!hvt)
		वापस शून्य;

	hvt->cn_id.idx = cn_idx;
	hvt->cn_id.val = cn_val;

	hvt->mdev.minor = MISC_DYNAMIC_MINOR;
	hvt->mdev.name = name;

	hvt->fops.owner = THIS_MODULE;
	hvt->fops.पढ़ो = hvt_op_पढ़ो;
	hvt->fops.ग_लिखो = hvt_op_ग_लिखो;
	hvt->fops.poll = hvt_op_poll;
	hvt->fops.खोलो = hvt_op_खोलो;
	hvt->fops.release = hvt_op_release;

	hvt->mdev.fops = &hvt->fops;

	init_रुकोqueue_head(&hvt->ouपंचांगsg_q);
	mutex_init(&hvt->lock);
	init_completion(&hvt->release);

	spin_lock(&hvt_list_lock);
	list_add(&hvt->list, &hvt_list);
	spin_unlock(&hvt_list_lock);

	hvt->on_msg = on_msg;
	hvt->on_reset = on_reset;

	अगर (misc_रेजिस्टर(&hvt->mdev))
		जाओ err_मुक्त_hvt;

	/* Use cn_id.idx/cn_id.val to determine अगर we need to setup netlink */
	अगर (hvt->cn_id.idx > 0 && hvt->cn_id.val > 0 &&
	    cn_add_callback(&hvt->cn_id, name, hvt_cn_callback))
		जाओ err_मुक्त_hvt;

	वापस hvt;

err_मुक्त_hvt:
	spin_lock(&hvt_list_lock);
	list_del(&hvt->list);
	spin_unlock(&hvt_list_lock);
	kमुक्त(hvt);
	वापस शून्य;
पूर्ण

व्योम hvutil_transport_destroy(काष्ठा hvutil_transport *hvt)
अणु
	पूर्णांक mode_old;

	mutex_lock(&hvt->lock);
	mode_old = hvt->mode;
	hvt->mode = HVUTIL_TRANSPORT_DESTROY;
	wake_up_पूर्णांकerruptible(&hvt->ouपंचांगsg_q);
	mutex_unlock(&hvt->lock);

	/*
	 * In हाल we were in 'chardev' mode we still have an खोलो fd so we
	 * have to defer मुक्तing the device. Netlink पूर्णांकerface can be मुक्तd
	 * now.
	 */
	spin_lock(&hvt_list_lock);
	list_del(&hvt->list);
	spin_unlock(&hvt_list_lock);
	अगर (hvt->cn_id.idx > 0 && hvt->cn_id.val > 0)
		cn_del_callback(&hvt->cn_id);

	अगर (mode_old == HVUTIL_TRANSPORT_CHARDEV)
		रुको_क्रम_completion(&hvt->release);

	hvt_transport_मुक्त(hvt);
पूर्ण
