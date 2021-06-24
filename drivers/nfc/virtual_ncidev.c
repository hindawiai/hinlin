<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtual NCI device simulation driver
 *
 * Copyright (C) 2020 Samsung Electrnoics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <net/nfc/nci_core.h>

क्रमागत भव_ncidev_mode अणु
	भव_ncidev_enabled,
	भव_ncidev_disabled,
	भव_ncidev_disabling,
पूर्ण;

#घोषणा IOCTL_GET_NCIDEV_IDX    0
#घोषणा VIRTUAL_NFC_PROTOCOLS	(NFC_PROTO_JEWEL_MASK | \
				 NFC_PROTO_MIFARE_MASK | \
				 NFC_PROTO_FELICA_MASK | \
				 NFC_PROTO_ISO14443_MASK | \
				 NFC_PROTO_ISO14443_B_MASK | \
				 NFC_PROTO_ISO15693_MASK)

अटल क्रमागत भव_ncidev_mode state;
अटल काष्ठा miscdevice miscdev;
अटल काष्ठा sk_buff *send_buff;
अटल काष्ठा nci_dev *ndev;
अटल DEFINE_MUTEX(nci_mutex);

अटल पूर्णांक भव_nci_खोलो(काष्ठा nci_dev *ndev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक भव_nci_बंद(काष्ठा nci_dev *ndev)
अणु
	mutex_lock(&nci_mutex);
	kमुक्त_skb(send_buff);
	send_buff = शून्य;
	mutex_unlock(&nci_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक भव_nci_send(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	mutex_lock(&nci_mutex);
	अगर (state != भव_ncidev_enabled) अणु
		mutex_unlock(&nci_mutex);
		वापस 0;
	पूर्ण

	अगर (send_buff) अणु
		mutex_unlock(&nci_mutex);
		वापस -1;
	पूर्ण
	send_buff = skb_copy(skb, GFP_KERNEL);
	mutex_unlock(&nci_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा nci_ops भव_nci_ops = अणु
	.खोलो = भव_nci_खोलो,
	.बंद = भव_nci_बंद,
	.send = भव_nci_send
पूर्ण;

अटल sमाप_प्रकार भव_ncidev_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार actual_len;

	mutex_lock(&nci_mutex);
	अगर (!send_buff) अणु
		mutex_unlock(&nci_mutex);
		वापस 0;
	पूर्ण

	actual_len = min_t(माप_प्रकार, count, send_buff->len);

	अगर (copy_to_user(buf, send_buff->data, actual_len)) अणु
		mutex_unlock(&nci_mutex);
		वापस -EFAULT;
	पूर्ण

	skb_pull(send_buff, actual_len);
	अगर (send_buff->len == 0) अणु
		consume_skb(send_buff);
		send_buff = शून्य;
	पूर्ण
	mutex_unlock(&nci_mutex);

	वापस actual_len;
पूर्ण

अटल sमाप_प्रकार भव_ncidev_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(count, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (copy_from_user(skb_put(skb, count), buf, count)) अणु
		kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण

	nci_recv_frame(ndev, skb);
	वापस count;
पूर्ण

अटल पूर्णांक भव_ncidev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&nci_mutex);
	अगर (state != भव_ncidev_disabled) अणु
		mutex_unlock(&nci_mutex);
		वापस -EBUSY;
	पूर्ण

	ndev = nci_allocate_device(&भव_nci_ops, VIRTUAL_NFC_PROTOCOLS,
				   0, 0);
	अगर (!ndev) अणु
		mutex_unlock(&nci_mutex);
		वापस -ENOMEM;
	पूर्ण

	ret = nci_रेजिस्टर_device(ndev);
	अगर (ret < 0) अणु
		nci_मुक्त_device(ndev);
		mutex_unlock(&nci_mutex);
		वापस ret;
	पूर्ण
	state = भव_ncidev_enabled;
	mutex_unlock(&nci_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक भव_ncidev_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&nci_mutex);

	अगर (state == भव_ncidev_enabled) अणु
		state = भव_ncidev_disabling;
		mutex_unlock(&nci_mutex);

		nci_unरेजिस्टर_device(ndev);
		nci_मुक्त_device(ndev);

		mutex_lock(&nci_mutex);
	पूर्ण

	state = भव_ncidev_disabled;
	mutex_unlock(&nci_mutex);

	वापस 0;
पूर्ण

अटल दीर्घ भव_ncidev_ioctl(काष्ठा file *flip, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा nfc_dev *nfc_dev = ndev->nfc_dev;
	व्योम __user *p = (व्योम __user *)arg;

	अगर (cmd != IOCTL_GET_NCIDEV_IDX)
		वापस -ENOTTY;

	अगर (copy_to_user(p, &nfc_dev->idx, माप(nfc_dev->idx)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations भव_ncidev_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = भव_ncidev_पढ़ो,
	.ग_लिखो = भव_ncidev_ग_लिखो,
	.खोलो = भव_ncidev_खोलो,
	.release = भव_ncidev_बंद,
	.unlocked_ioctl = भव_ncidev_ioctl
पूर्ण;

अटल पूर्णांक __init भव_ncidev_init(व्योम)
अणु
	state = भव_ncidev_disabled;
	miscdev.minor = MISC_DYNAMIC_MINOR;
	miscdev.name = "virtual_nci";
	miscdev.fops = &भव_ncidev_fops;
	miscdev.mode = S_IALLUGO;

	वापस misc_रेजिस्टर(&miscdev);
पूर्ण

अटल व्योम __निकास भव_ncidev_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&miscdev);
पूर्ण

module_init(भव_ncidev_init);
module_निकास(भव_ncidev_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Virtual NCI device simulation driver");
MODULE_AUTHOR("Bongsu Jeon <bongsu.jeon@samsung.com>");
