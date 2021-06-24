<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2009 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 *
 * test virtio server in host kernel.
 */

#समावेश <linux/compat.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/vhost.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>

#समावेश "test.h"
#समावेश "vhost.h"

/* Max number of bytes transferred beक्रमe requeueing the job.
 * Using this limit prevents one virtqueue from starving others. */
#घोषणा VHOST_TEST_WEIGHT 0x80000

/* Max number of packets transferred beक्रमe requeueing the job.
 * Using this limit prevents one virtqueue from starving others with
 * pkts.
 */
#घोषणा VHOST_TEST_PKT_WEIGHT 256

क्रमागत अणु
	VHOST_TEST_VQ = 0,
	VHOST_TEST_VQ_MAX = 1,
पूर्ण;

काष्ठा vhost_test अणु
	काष्ठा vhost_dev dev;
	काष्ठा vhost_virtqueue vqs[VHOST_TEST_VQ_MAX];
पूर्ण;

/* Expects to be always run from workqueue - which acts as
 * पढ़ो-size critical section क्रम our kind of RCU. */
अटल व्योम handle_vq(काष्ठा vhost_test *n)
अणु
	काष्ठा vhost_virtqueue *vq = &n->vqs[VHOST_TEST_VQ];
	अचिन्हित out, in;
	पूर्णांक head;
	माप_प्रकार len, total_len = 0;
	व्योम *निजी;

	mutex_lock(&vq->mutex);
	निजी = vhost_vq_get_backend(vq);
	अगर (!निजी) अणु
		mutex_unlock(&vq->mutex);
		वापस;
	पूर्ण

	vhost_disable_notअगरy(&n->dev, vq);

	क्रम (;;) अणु
		head = vhost_get_vq_desc(vq, vq->iov,
					 ARRAY_SIZE(vq->iov),
					 &out, &in,
					 शून्य, शून्य);
		/* On error, stop handling until the next kick. */
		अगर (unlikely(head < 0))
			अवरोध;
		/* Nothing new?  Wait क्रम eventfd to tell us they refilled. */
		अगर (head == vq->num) अणु
			अगर (unlikely(vhost_enable_notअगरy(&n->dev, vq))) अणु
				vhost_disable_notअगरy(&n->dev, vq);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (in) अणु
			vq_err(vq, "Unexpected descriptor format for TX: "
			       "out %d, int %d\n", out, in);
			अवरोध;
		पूर्ण
		len = iov_length(vq->iov, out);
		/* Sanity check */
		अगर (!len) अणु
			vq_err(vq, "Unexpected 0 len for TX\n");
			अवरोध;
		पूर्ण
		vhost_add_used_and_संकेत(&n->dev, vq, head, 0);
		total_len += len;
		अगर (unlikely(vhost_exceeds_weight(vq, 0, total_len)))
			अवरोध;
	पूर्ण

	mutex_unlock(&vq->mutex);
पूर्ण

अटल व्योम handle_vq_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						  poll.work);
	काष्ठा vhost_test *n = container_of(vq->dev, काष्ठा vhost_test, dev);

	handle_vq(n);
पूर्ण

अटल पूर्णांक vhost_test_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा vhost_test *n = kदो_स्मृति(माप *n, GFP_KERNEL);
	काष्ठा vhost_dev *dev;
	काष्ठा vhost_virtqueue **vqs;

	अगर (!n)
		वापस -ENOMEM;
	vqs = kदो_स्मृति_array(VHOST_TEST_VQ_MAX, माप(*vqs), GFP_KERNEL);
	अगर (!vqs) अणु
		kमुक्त(n);
		वापस -ENOMEM;
	पूर्ण

	dev = &n->dev;
	vqs[VHOST_TEST_VQ] = &n->vqs[VHOST_TEST_VQ];
	n->vqs[VHOST_TEST_VQ].handle_kick = handle_vq_kick;
	vhost_dev_init(dev, vqs, VHOST_TEST_VQ_MAX, UIO_MAXIOV,
		       VHOST_TEST_PKT_WEIGHT, VHOST_TEST_WEIGHT, true, शून्य);

	f->निजी_data = n;

	वापस 0;
पूर्ण

अटल व्योम *vhost_test_stop_vq(काष्ठा vhost_test *n,
				काष्ठा vhost_virtqueue *vq)
अणु
	व्योम *निजी;

	mutex_lock(&vq->mutex);
	निजी = vhost_vq_get_backend(vq);
	vhost_vq_set_backend(vq, शून्य);
	mutex_unlock(&vq->mutex);
	वापस निजी;
पूर्ण

अटल व्योम vhost_test_stop(काष्ठा vhost_test *n, व्योम **निजीp)
अणु
	*निजीp = vhost_test_stop_vq(n, n->vqs + VHOST_TEST_VQ);
पूर्ण

अटल व्योम vhost_test_flush_vq(काष्ठा vhost_test *n, पूर्णांक index)
अणु
	vhost_poll_flush(&n->vqs[index].poll);
पूर्ण

अटल व्योम vhost_test_flush(काष्ठा vhost_test *n)
अणु
	vhost_test_flush_vq(n, VHOST_TEST_VQ);
पूर्ण

अटल पूर्णांक vhost_test_release(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा vhost_test *n = f->निजी_data;
	व्योम  *निजी;

	vhost_test_stop(n, &निजी);
	vhost_test_flush(n);
	vhost_dev_stop(&n->dev);
	vhost_dev_cleanup(&n->dev);
	/* We करो an extra flush beक्रमe मुक्तing memory,
	 * since jobs can re-queue themselves. */
	vhost_test_flush(n);
	kमुक्त(n);
	वापस 0;
पूर्ण

अटल दीर्घ vhost_test_run(काष्ठा vhost_test *n, पूर्णांक test)
अणु
	व्योम *priv, *oldpriv;
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक r, index;

	अगर (test < 0 || test > 1)
		वापस -EINVAL;

	mutex_lock(&n->dev.mutex);
	r = vhost_dev_check_owner(&n->dev);
	अगर (r)
		जाओ err;

	क्रम (index = 0; index < n->dev.nvqs; ++index) अणु
		/* Verअगरy that ring has been setup correctly. */
		अगर (!vhost_vq_access_ok(&n->vqs[index])) अणु
			r = -EFAULT;
			जाओ err;
		पूर्ण
	पूर्ण

	क्रम (index = 0; index < n->dev.nvqs; ++index) अणु
		vq = n->vqs + index;
		mutex_lock(&vq->mutex);
		priv = test ? n : शून्य;

		/* start polling new socket */
		oldpriv = vhost_vq_get_backend(vq);
		vhost_vq_set_backend(vq, priv);

		r = vhost_vq_init_access(&n->vqs[index]);

		mutex_unlock(&vq->mutex);

		अगर (r)
			जाओ err;

		अगर (oldpriv) अणु
			vhost_test_flush_vq(n, index);
		पूर्ण
	पूर्ण

	mutex_unlock(&n->dev.mutex);
	वापस 0;

err:
	mutex_unlock(&n->dev.mutex);
	वापस r;
पूर्ण

अटल दीर्घ vhost_test_reset_owner(काष्ठा vhost_test *n)
अणु
	व्योम *priv = शून्य;
	दीर्घ err;
	काष्ठा vhost_iotlb *umem;

	mutex_lock(&n->dev.mutex);
	err = vhost_dev_check_owner(&n->dev);
	अगर (err)
		जाओ करोne;
	umem = vhost_dev_reset_owner_prepare();
	अगर (!umem) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	vhost_test_stop(n, &priv);
	vhost_test_flush(n);
	vhost_dev_stop(&n->dev);
	vhost_dev_reset_owner(&n->dev, umem);
करोne:
	mutex_unlock(&n->dev.mutex);
	वापस err;
पूर्ण

अटल पूर्णांक vhost_test_set_features(काष्ठा vhost_test *n, u64 features)
अणु
	काष्ठा vhost_virtqueue *vq;

	mutex_lock(&n->dev.mutex);
	अगर ((features & (1 << VHOST_F_LOG_ALL)) &&
	    !vhost_log_access_ok(&n->dev)) अणु
		mutex_unlock(&n->dev.mutex);
		वापस -EFAULT;
	पूर्ण
	vq = &n->vqs[VHOST_TEST_VQ];
	mutex_lock(&vq->mutex);
	vq->acked_features = features;
	mutex_unlock(&vq->mutex);
	mutex_unlock(&n->dev.mutex);
	वापस 0;
पूर्ण

अटल दीर्घ vhost_test_set_backend(काष्ठा vhost_test *n, अचिन्हित index, पूर्णांक fd)
अणु
	अटल व्योम *backend;

	स्थिर bool enable = fd != -1;
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक r;

	mutex_lock(&n->dev.mutex);
	r = vhost_dev_check_owner(&n->dev);
	अगर (r)
		जाओ err;

	अगर (index >= VHOST_TEST_VQ_MAX) अणु
		r = -ENOBUFS;
		जाओ err;
	पूर्ण
	vq = &n->vqs[index];
	mutex_lock(&vq->mutex);

	/* Verअगरy that ring has been setup correctly. */
	अगर (!vhost_vq_access_ok(vq)) अणु
		r = -EFAULT;
		जाओ err_vq;
	पूर्ण
	अगर (!enable) अणु
		vhost_poll_stop(&vq->poll);
		backend = vhost_vq_get_backend(vq);
		vhost_vq_set_backend(vq, शून्य);
	पूर्ण अन्यथा अणु
		vhost_vq_set_backend(vq, backend);
		r = vhost_vq_init_access(vq);
		अगर (r == 0)
			r = vhost_poll_start(&vq->poll, vq->kick);
	पूर्ण

	mutex_unlock(&vq->mutex);

	अगर (enable) अणु
		vhost_test_flush_vq(n, index);
	पूर्ण

	mutex_unlock(&n->dev.mutex);
	वापस 0;

err_vq:
	mutex_unlock(&vq->mutex);
err:
	mutex_unlock(&n->dev.mutex);
	वापस r;
पूर्ण

अटल दीर्घ vhost_test_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक ioctl,
			     अचिन्हित दीर्घ arg)
अणु
	काष्ठा vhost_vring_file backend;
	काष्ठा vhost_test *n = f->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	u64 __user *featurep = argp;
	पूर्णांक test;
	u64 features;
	पूर्णांक r;
	चयन (ioctl) अणु
	हाल VHOST_TEST_RUN:
		अगर (copy_from_user(&test, argp, माप test))
			वापस -EFAULT;
		वापस vhost_test_run(n, test);
	हाल VHOST_TEST_SET_BACKEND:
		अगर (copy_from_user(&backend, argp, माप backend))
			वापस -EFAULT;
		वापस vhost_test_set_backend(n, backend.index, backend.fd);
	हाल VHOST_GET_FEATURES:
		features = VHOST_FEATURES;
		अगर (copy_to_user(featurep, &features, माप features))
			वापस -EFAULT;
		वापस 0;
	हाल VHOST_SET_FEATURES:
		prपूर्णांकk(KERN_ERR "1\n");
		अगर (copy_from_user(&features, featurep, माप features))
			वापस -EFAULT;
		prपूर्णांकk(KERN_ERR "2\n");
		अगर (features & ~VHOST_FEATURES)
			वापस -EOPNOTSUPP;
		prपूर्णांकk(KERN_ERR "3\n");
		वापस vhost_test_set_features(n, features);
	हाल VHOST_RESET_OWNER:
		वापस vhost_test_reset_owner(n);
	शेष:
		mutex_lock(&n->dev.mutex);
		r = vhost_dev_ioctl(&n->dev, ioctl, argp);
                अगर (r == -ENOIOCTLCMD)
                        r = vhost_vring_ioctl(&n->dev, ioctl, argp);
		vhost_test_flush(n);
		mutex_unlock(&n->dev.mutex);
		वापस r;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations vhost_test_fops = अणु
	.owner          = THIS_MODULE,
	.release        = vhost_test_release,
	.unlocked_ioctl = vhost_test_ioctl,
	.compat_ioctl   = compat_ptr_ioctl,
	.खोलो           = vhost_test_खोलो,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice vhost_test_misc = अणु
	MISC_DYNAMIC_MINOR,
	"vhost-test",
	&vhost_test_fops,
पूर्ण;
module_misc_device(vhost_test_misc);

MODULE_VERSION("0.0.1");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Michael S. Tsirkin");
MODULE_DESCRIPTION("Host kernel side for virtio simulator");
