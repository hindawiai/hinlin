<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Linaro Ltd */

#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/uaccess.h>

#समावेश "qrtr.h"

काष्ठा qrtr_tun अणु
	काष्ठा qrtr_endpoपूर्णांक ep;

	काष्ठा sk_buff_head queue;
	रुको_queue_head_t पढ़ोq;
पूर्ण;

अटल पूर्णांक qrtr_tun_send(काष्ठा qrtr_endpoपूर्णांक *ep, काष्ठा sk_buff *skb)
अणु
	काष्ठा qrtr_tun *tun = container_of(ep, काष्ठा qrtr_tun, ep);

	skb_queue_tail(&tun->queue, skb);

	/* wake up any blocking processes, रुकोing क्रम new data */
	wake_up_पूर्णांकerruptible(&tun->पढ़ोq);

	वापस 0;
पूर्ण

अटल पूर्णांक qrtr_tun_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा qrtr_tun *tun;
	पूर्णांक ret;

	tun = kzalloc(माप(*tun), GFP_KERNEL);
	अगर (!tun)
		वापस -ENOMEM;

	skb_queue_head_init(&tun->queue);
	init_रुकोqueue_head(&tun->पढ़ोq);

	tun->ep.xmit = qrtr_tun_send;

	filp->निजी_data = tun;

	ret = qrtr_endpoपूर्णांक_रेजिस्टर(&tun->ep, QRTR_EP_NID_AUTO);
	अगर (ret)
		जाओ out;

	वापस 0;

out:
	filp->निजी_data = शून्य;
	kमुक्त(tun);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार qrtr_tun_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा qrtr_tun *tun = filp->निजी_data;
	काष्ठा sk_buff *skb;
	पूर्णांक count;

	जबतक (!(skb = skb_dequeue(&tun->queue))) अणु
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		/* Wait until we get data or the endpoपूर्णांक goes away */
		अगर (रुको_event_पूर्णांकerruptible(tun->पढ़ोq,
					     !skb_queue_empty(&tun->queue)))
			वापस -ERESTARTSYS;
	पूर्ण

	count = min_t(माप_प्रकार, iov_iter_count(to), skb->len);
	अगर (copy_to_iter(skb->data, count, to) != count)
		count = -EFAULT;

	kमुक्त_skb(skb);

	वापस count;
पूर्ण

अटल sमाप_प्रकार qrtr_tun_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा qrtr_tun *tun = filp->निजी_data;
	माप_प्रकार len = iov_iter_count(from);
	sमाप_प्रकार ret;
	व्योम *kbuf;

	अगर (!len)
		वापस -EINVAL;

	अगर (len > KMALLOC_MAX_SIZE)
		वापस -ENOMEM;

	kbuf = kzalloc(len, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	अगर (!copy_from_iter_full(kbuf, len, from)) अणु
		kमुक्त(kbuf);
		वापस -EFAULT;
	पूर्ण

	ret = qrtr_endpoपूर्णांक_post(&tun->ep, kbuf, len);

	kमुक्त(kbuf);
	वापस ret < 0 ? ret : len;
पूर्ण

अटल __poll_t qrtr_tun_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा qrtr_tun *tun = filp->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filp, &tun->पढ़ोq, रुको);

	अगर (!skb_queue_empty(&tun->queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल पूर्णांक qrtr_tun_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा qrtr_tun *tun = filp->निजी_data;

	qrtr_endpoपूर्णांक_unरेजिस्टर(&tun->ep);

	/* Discard all SKBs */
	skb_queue_purge(&tun->queue);

	kमुक्त(tun);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations qrtr_tun_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = qrtr_tun_खोलो,
	.poll = qrtr_tun_poll,
	.पढ़ो_iter = qrtr_tun_पढ़ो_iter,
	.ग_लिखो_iter = qrtr_tun_ग_लिखो_iter,
	.release = qrtr_tun_release,
पूर्ण;

अटल काष्ठा miscdevice qrtr_tun_miscdev = अणु
	MISC_DYNAMIC_MINOR,
	"qrtr-tun",
	&qrtr_tun_ops,
पूर्ण;

अटल पूर्णांक __init qrtr_tun_init(व्योम)
अणु
	पूर्णांक ret;

	ret = misc_रेजिस्टर(&qrtr_tun_miscdev);
	अगर (ret)
		pr_err("failed to register Qualcomm IPC Router tun device\n");

	वापस ret;
पूर्ण

अटल व्योम __निकास qrtr_tun_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&qrtr_tun_miscdev);
पूर्ण

module_init(qrtr_tun_init);
module_निकास(qrtr_tun_निकास);

MODULE_DESCRIPTION("Qualcomm IPC Router TUN device");
MODULE_LICENSE("GPL v2");
