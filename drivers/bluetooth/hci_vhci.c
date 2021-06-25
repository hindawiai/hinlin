<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth भव HCI driver
 *
 *  Copyright (C) 2000-2001  Qualcomm Incorporated
 *  Copyright (C) 2002-2003  Maxim Krasnyansky <maxk@qualcomm.com>
 *  Copyright (C) 2004-2006  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/poll.h>

#समावेश <linux/skbuff.h>
#समावेश <linux/miscdevice.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#घोषणा VERSION "1.5"

अटल bool amp;

काष्ठा vhci_data अणु
	काष्ठा hci_dev *hdev;

	रुको_queue_head_t पढ़ो_रुको;
	काष्ठा sk_buff_head पढ़ोq;

	काष्ठा mutex खोलो_mutex;
	काष्ठा delayed_work खोलो_समयout;
पूर्ण;

अटल पूर्णांक vhci_खोलो_dev(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vhci_बंद_dev(काष्ठा hci_dev *hdev)
अणु
	काष्ठा vhci_data *data = hci_get_drvdata(hdev);

	skb_queue_purge(&data->पढ़ोq);

	वापस 0;
पूर्ण

अटल पूर्णांक vhci_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा vhci_data *data = hci_get_drvdata(hdev);

	skb_queue_purge(&data->पढ़ोq);

	वापस 0;
पूर्ण

अटल पूर्णांक vhci_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा vhci_data *data = hci_get_drvdata(hdev);

	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);
	skb_queue_tail(&data->पढ़ोq, skb);

	wake_up_पूर्णांकerruptible(&data->पढ़ो_रुको);
	वापस 0;
पूर्ण

अटल पूर्णांक __vhci_create_device(काष्ठा vhci_data *data, __u8 opcode)
अणु
	काष्ठा hci_dev *hdev;
	काष्ठा sk_buff *skb;
	__u8 dev_type;

	अगर (data->hdev)
		वापस -EBADFD;

	/* bits 0-1 are dev_type (Primary or AMP) */
	dev_type = opcode & 0x03;

	अगर (dev_type != HCI_PRIMARY && dev_type != HCI_AMP)
		वापस -EINVAL;

	/* bits 2-5 are reserved (must be zero) */
	अगर (opcode & 0x3c)
		वापस -EINVAL;

	skb = bt_skb_alloc(4, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	data->hdev = hdev;

	hdev->bus = HCI_VIRTUAL;
	hdev->dev_type = dev_type;
	hci_set_drvdata(hdev, data);

	hdev->खोलो  = vhci_खोलो_dev;
	hdev->बंद = vhci_बंद_dev;
	hdev->flush = vhci_flush;
	hdev->send  = vhci_send_frame;

	/* bit 6 is क्रम बाह्यal configuration */
	अगर (opcode & 0x40)
		set_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks);

	/* bit 7 is क्रम raw device */
	अगर (opcode & 0x80)
		set_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks);

	अगर (hci_रेजिस्टर_dev(hdev) < 0) अणु
		BT_ERR("Can't register HCI device");
		hci_मुक्त_dev(hdev);
		data->hdev = शून्य;
		kमुक्त_skb(skb);
		वापस -EBUSY;
	पूर्ण

	hci_skb_pkt_type(skb) = HCI_VENDOR_PKT;

	skb_put_u8(skb, 0xff);
	skb_put_u8(skb, opcode);
	put_unaligned_le16(hdev->id, skb_put(skb, 2));
	skb_queue_tail(&data->पढ़ोq, skb);

	wake_up_पूर्णांकerruptible(&data->पढ़ो_रुको);
	वापस 0;
पूर्ण

अटल पूर्णांक vhci_create_device(काष्ठा vhci_data *data, __u8 opcode)
अणु
	पूर्णांक err;

	mutex_lock(&data->खोलो_mutex);
	err = __vhci_create_device(data, opcode);
	mutex_unlock(&data->खोलो_mutex);

	वापस err;
पूर्ण

अटल अंतरभूत sमाप_प्रकार vhci_get_user(काष्ठा vhci_data *data,
				    काष्ठा iov_iter *from)
अणु
	माप_प्रकार len = iov_iter_count(from);
	काष्ठा sk_buff *skb;
	__u8 pkt_type, opcode;
	पूर्णांक ret;

	अगर (len < 2 || len > HCI_MAX_FRAME_SIZE)
		वापस -EINVAL;

	skb = bt_skb_alloc(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (!copy_from_iter_full(skb_put(skb, len), len, from)) अणु
		kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण

	pkt_type = *((__u8 *) skb->data);
	skb_pull(skb, 1);

	चयन (pkt_type) अणु
	हाल HCI_EVENT_PKT:
	हाल HCI_ACLDATA_PKT:
	हाल HCI_SCODATA_PKT:
	हाल HCI_ISODATA_PKT:
		अगर (!data->hdev) अणु
			kमुक्त_skb(skb);
			वापस -ENODEV;
		पूर्ण

		hci_skb_pkt_type(skb) = pkt_type;

		ret = hci_recv_frame(data->hdev, skb);
		अवरोध;

	हाल HCI_VENDOR_PKT:
		cancel_delayed_work_sync(&data->खोलो_समयout);

		opcode = *((__u8 *) skb->data);
		skb_pull(skb, 1);

		अगर (skb->len > 0) अणु
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण

		kमुक्त_skb(skb);

		ret = vhci_create_device(data, opcode);
		अवरोध;

	शेष:
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	वापस (ret < 0) ? ret : len;
पूर्ण

अटल अंतरभूत sमाप_प्रकार vhci_put_user(काष्ठा vhci_data *data,
				    काष्ठा sk_buff *skb,
				    अक्षर __user *buf, पूर्णांक count)
अणु
	अक्षर __user *ptr = buf;
	पूर्णांक len;

	len = min_t(अचिन्हित पूर्णांक, skb->len, count);

	अगर (copy_to_user(ptr, skb->data, len))
		वापस -EFAULT;

	अगर (!data->hdev)
		वापस len;

	data->hdev->stat.byte_tx += len;

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		data->hdev->stat.cmd_tx++;
		अवरोध;
	हाल HCI_ACLDATA_PKT:
		data->hdev->stat.acl_tx++;
		अवरोध;
	हाल HCI_SCODATA_PKT:
		data->hdev->stat.sco_tx++;
		अवरोध;
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार vhci_पढ़ो(काष्ठा file *file,
			 अक्षर __user *buf, माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा vhci_data *data = file->निजी_data;
	काष्ठा sk_buff *skb;
	sमाप_प्रकार ret = 0;

	जबतक (count) अणु
		skb = skb_dequeue(&data->पढ़ोq);
		अगर (skb) अणु
			ret = vhci_put_user(data, skb, buf, count);
			अगर (ret < 0)
				skb_queue_head(&data->पढ़ोq, skb);
			अन्यथा
				kमुक्त_skb(skb);
			अवरोध;
		पूर्ण

		अगर (file->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण

		ret = रुको_event_पूर्णांकerruptible(data->पढ़ो_रुको,
					       !skb_queue_empty(&data->पढ़ोq));
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार vhci_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा vhci_data *data = file->निजी_data;

	वापस vhci_get_user(data, from);
पूर्ण

अटल __poll_t vhci_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा vhci_data *data = file->निजी_data;

	poll_रुको(file, &data->पढ़ो_रुको, रुको);

	अगर (!skb_queue_empty(&data->पढ़ोq))
		वापस EPOLLIN | EPOLLRDNORM;

	वापस EPOLLOUT | EPOLLWRNORM;
पूर्ण

अटल व्योम vhci_खोलो_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vhci_data *data = container_of(work, काष्ठा vhci_data,
					      खोलो_समयout.work);

	vhci_create_device(data, amp ? HCI_AMP : HCI_PRIMARY);
पूर्ण

अटल पूर्णांक vhci_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vhci_data *data;

	data = kzalloc(माप(काष्ठा vhci_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	skb_queue_head_init(&data->पढ़ोq);
	init_रुकोqueue_head(&data->पढ़ो_रुको);

	mutex_init(&data->खोलो_mutex);
	INIT_DELAYED_WORK(&data->खोलो_समयout, vhci_खोलो_समयout);

	file->निजी_data = data;
	nonseekable_खोलो(inode, file);

	schedule_delayed_work(&data->खोलो_समयout, msecs_to_jअगरfies(1000));

	वापस 0;
पूर्ण

अटल पूर्णांक vhci_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vhci_data *data = file->निजी_data;
	काष्ठा hci_dev *hdev;

	cancel_delayed_work_sync(&data->खोलो_समयout);

	hdev = data->hdev;

	अगर (hdev) अणु
		hci_unरेजिस्टर_dev(hdev);
		hci_मुक्त_dev(hdev);
	पूर्ण

	skb_queue_purge(&data->पढ़ोq);
	file->निजी_data = शून्य;
	kमुक्त(data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations vhci_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= vhci_पढ़ो,
	.ग_लिखो_iter	= vhci_ग_लिखो,
	.poll		= vhci_poll,
	.खोलो		= vhci_खोलो,
	.release	= vhci_release,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice vhci_miscdev = अणु
	.name	= "vhci",
	.fops	= &vhci_fops,
	.minor	= VHCI_MINOR,
पूर्ण;
module_misc_device(vhci_miscdev);

module_param(amp, bool, 0644);
MODULE_PARM_DESC(amp, "Create AMP controller device");

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth virtual HCI driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS("devname:vhci");
MODULE_ALIAS_MISCDEV(VHCI_MINOR);
