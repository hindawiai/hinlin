<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NFC hardware simulation driver
 * Copyright (c) 2013, Intel Corporation.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/nfc.h>
#समावेश <net/nfc/digital.h>

#घोषणा NFCSIM_ERR(d, fmt, args...) nfc_err(&d->nfc_digital_dev->nfc_dev->dev, \
					    "%s: " fmt, __func__, ## args)

#घोषणा NFCSIM_DBG(d, fmt, args...) dev_dbg(&d->nfc_digital_dev->nfc_dev->dev, \
					    "%s: " fmt, __func__, ## args)

#घोषणा NFCSIM_VERSION "0.2"

#घोषणा NFCSIM_MODE_NONE	0
#घोषणा NFCSIM_MODE_INITIATOR	1
#घोषणा NFCSIM_MODE_TARGET	2

#घोषणा NFCSIM_CAPABILITIES (NFC_DIGITAL_DRV_CAPS_IN_CRC   | \
			     NFC_DIGITAL_DRV_CAPS_TG_CRC)

काष्ठा nfcsim अणु
	काष्ठा nfc_digital_dev *nfc_digital_dev;

	काष्ठा work_काष्ठा recv_work;
	काष्ठा delayed_work send_work;

	काष्ठा nfcsim_link *link_in;
	काष्ठा nfcsim_link *link_out;

	bool up;
	u8 mode;
	u8 rf_tech;

	u16 recv_समयout;

	nfc_digital_cmd_complete_t cb;
	व्योम *arg;

	u8 dropframe;
पूर्ण;

काष्ठा nfcsim_link अणु
	काष्ठा mutex lock;

	u8 rf_tech;
	u8 mode;

	u8 shutकरोwn;

	काष्ठा sk_buff *skb;
	रुको_queue_head_t recv_रुको;
	u8 cond;
पूर्ण;

अटल काष्ठा nfcsim_link *nfcsim_link_new(व्योम)
अणु
	काष्ठा nfcsim_link *link;

	link = kzalloc(माप(काष्ठा nfcsim_link), GFP_KERNEL);
	अगर (!link)
		वापस शून्य;

	mutex_init(&link->lock);
	init_रुकोqueue_head(&link->recv_रुको);

	वापस link;
पूर्ण

अटल व्योम nfcsim_link_मुक्त(काष्ठा nfcsim_link *link)
अणु
	dev_kमुक्त_skb(link->skb);
	kमुक्त(link);
पूर्ण

अटल व्योम nfcsim_link_recv_wake(काष्ठा nfcsim_link *link)
अणु
	link->cond = 1;
	wake_up_पूर्णांकerruptible(&link->recv_रुको);
पूर्ण

अटल व्योम nfcsim_link_set_skb(काष्ठा nfcsim_link *link, काष्ठा sk_buff *skb,
				u8 rf_tech, u8 mode)
अणु
	mutex_lock(&link->lock);

	dev_kमुक्त_skb(link->skb);
	link->skb = skb;
	link->rf_tech = rf_tech;
	link->mode = mode;

	mutex_unlock(&link->lock);
पूर्ण

अटल व्योम nfcsim_link_recv_cancel(काष्ठा nfcsim_link *link)
अणु
	mutex_lock(&link->lock);

	link->mode = NFCSIM_MODE_NONE;

	mutex_unlock(&link->lock);

	nfcsim_link_recv_wake(link);
पूर्ण

अटल व्योम nfcsim_link_shutकरोwn(काष्ठा nfcsim_link *link)
अणु
	mutex_lock(&link->lock);

	link->shutकरोwn = 1;
	link->mode = NFCSIM_MODE_NONE;

	mutex_unlock(&link->lock);

	nfcsim_link_recv_wake(link);
पूर्ण

अटल काष्ठा sk_buff *nfcsim_link_recv_skb(काष्ठा nfcsim_link *link,
					    पूर्णांक समयout, u8 rf_tech, u8 mode)
अणु
	पूर्णांक rc;
	काष्ठा sk_buff *skb;

	rc = रुको_event_पूर्णांकerruptible_समयout(link->recv_रुको,
					      link->cond,
					      msecs_to_jअगरfies(समयout));

	mutex_lock(&link->lock);

	skb = link->skb;
	link->skb = शून्य;

	अगर (!rc) अणु
		rc = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण

	अगर (!skb || link->rf_tech != rf_tech || link->mode == mode) अणु
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (link->shutकरोwn) अणु
		rc = -ENODEV;
		जाओ करोne;
	पूर्ण

करोne:
	mutex_unlock(&link->lock);

	अगर (rc < 0) अणु
		dev_kमुक्त_skb(skb);
		skb = ERR_PTR(rc);
	पूर्ण

	link->cond = 0;

	वापस skb;
पूर्ण

अटल व्योम nfcsim_send_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfcsim *dev = container_of(work, काष्ठा nfcsim, send_work.work);

	/*
	 * To effectively send data, the device just wake up its link_out which
	 * is the link_in of the peer device. The exchanged skb has alपढ़ोy been
	 * stored in the dev->link_out through nfcsim_link_set_skb().
	 */
	nfcsim_link_recv_wake(dev->link_out);
पूर्ण

अटल व्योम nfcsim_recv_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfcsim *dev = container_of(work, काष्ठा nfcsim, recv_work);
	काष्ठा sk_buff *skb;

	skb = nfcsim_link_recv_skb(dev->link_in, dev->recv_समयout,
				   dev->rf_tech, dev->mode);

	अगर (!dev->up) अणु
		NFCSIM_ERR(dev, "Device is down\n");

		अगर (!IS_ERR(skb))
			dev_kमुक्त_skb(skb);

		skb = ERR_PTR(-ENODEV);
	पूर्ण

	dev->cb(dev->nfc_digital_dev, dev->arg, skb);
पूर्ण

अटल पूर्णांक nfcsim_send(काष्ठा nfc_digital_dev *ddev, काष्ठा sk_buff *skb,
		       u16 समयout, nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	काष्ठा nfcsim *dev = nfc_digital_get_drvdata(ddev);
	u8 delay;

	अगर (!dev->up) अणु
		NFCSIM_ERR(dev, "Device is down\n");
		वापस -ENODEV;
	पूर्ण

	dev->recv_समयout = समयout;
	dev->cb = cb;
	dev->arg = arg;

	schedule_work(&dev->recv_work);

	अगर (dev->dropframe) अणु
		NFCSIM_DBG(dev, "dropping frame (out of %d)\n", dev->dropframe);
		dev_kमुक्त_skb(skb);
		dev->dropframe--;

		वापस 0;
	पूर्ण

	अगर (skb) अणु
		nfcsim_link_set_skb(dev->link_out, skb, dev->rf_tech,
				    dev->mode);

		/* Add अक्रमom delay (between 3 and 10 ms) beक्रमe sending data */
		get_अक्रमom_bytes(&delay, 1);
		delay = 3 + (delay & 0x07);

		schedule_delayed_work(&dev->send_work, msecs_to_jअगरfies(delay));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nfcsim_पात_cmd(काष्ठा nfc_digital_dev *ddev)
अणु
	काष्ठा nfcsim *dev = nfc_digital_get_drvdata(ddev);

	nfcsim_link_recv_cancel(dev->link_in);
पूर्ण

अटल पूर्णांक nfcsim_चयन_rf(काष्ठा nfc_digital_dev *ddev, bool on)
अणु
	काष्ठा nfcsim *dev = nfc_digital_get_drvdata(ddev);

	dev->up = on;

	वापस 0;
पूर्ण

अटल पूर्णांक nfcsim_in_configure_hw(काष्ठा nfc_digital_dev *ddev,
					  पूर्णांक type, पूर्णांक param)
अणु
	काष्ठा nfcsim *dev = nfc_digital_get_drvdata(ddev);

	चयन (type) अणु
	हाल NFC_DIGITAL_CONFIG_RF_TECH:
		dev->up = true;
		dev->mode = NFCSIM_MODE_INITIATOR;
		dev->rf_tech = param;
		अवरोध;

	हाल NFC_DIGITAL_CONFIG_FRAMING:
		अवरोध;

	शेष:
		NFCSIM_ERR(dev, "Invalid configuration type: %d\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfcsim_in_send_cmd(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा sk_buff *skb, u16 समयout,
			       nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	वापस nfcsim_send(ddev, skb, समयout, cb, arg);
पूर्ण

अटल पूर्णांक nfcsim_tg_configure_hw(काष्ठा nfc_digital_dev *ddev,
					  पूर्णांक type, पूर्णांक param)
अणु
	काष्ठा nfcsim *dev = nfc_digital_get_drvdata(ddev);

	चयन (type) अणु
	हाल NFC_DIGITAL_CONFIG_RF_TECH:
		dev->up = true;
		dev->mode = NFCSIM_MODE_TARGET;
		dev->rf_tech = param;
		अवरोध;

	हाल NFC_DIGITAL_CONFIG_FRAMING:
		अवरोध;

	शेष:
		NFCSIM_ERR(dev, "Invalid configuration type: %d\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfcsim_tg_send_cmd(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा sk_buff *skb, u16 समयout,
			       nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	वापस nfcsim_send(ddev, skb, समयout, cb, arg);
पूर्ण

अटल पूर्णांक nfcsim_tg_listen(काष्ठा nfc_digital_dev *ddev, u16 समयout,
			    nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	वापस nfcsim_send(ddev, शून्य, समयout, cb, arg);
पूर्ण

अटल काष्ठा nfc_digital_ops nfcsim_digital_ops = अणु
	.in_configure_hw = nfcsim_in_configure_hw,
	.in_send_cmd = nfcsim_in_send_cmd,

	.tg_listen = nfcsim_tg_listen,
	.tg_configure_hw = nfcsim_tg_configure_hw,
	.tg_send_cmd = nfcsim_tg_send_cmd,

	.पात_cmd = nfcsim_पात_cmd,
	.चयन_rf = nfcsim_चयन_rf,
पूर्ण;

अटल काष्ठा dentry *nfcsim_debugfs_root;

अटल व्योम nfcsim_debugfs_init(व्योम)
अणु
	nfcsim_debugfs_root = debugfs_create_dir("nfcsim", शून्य);

	अगर (!nfcsim_debugfs_root)
		pr_err("Could not create debugfs entry\n");

पूर्ण

अटल व्योम nfcsim_debugfs_हटाओ(व्योम)
अणु
	debugfs_हटाओ_recursive(nfcsim_debugfs_root);
पूर्ण

अटल व्योम nfcsim_debugfs_init_dev(काष्ठा nfcsim *dev)
अणु
	काष्ठा dentry *dev_dir;
	अक्षर devname[5]; /* nfcX\0 */
	u32 idx;
	पूर्णांक n;

	अगर (!nfcsim_debugfs_root) अणु
		NFCSIM_ERR(dev, "nfcsim debugfs not initialized\n");
		वापस;
	पूर्ण

	idx = dev->nfc_digital_dev->nfc_dev->idx;
	n = snम_लिखो(devname, माप(devname), "nfc%d", idx);
	अगर (n >= माप(devname)) अणु
		NFCSIM_ERR(dev, "Could not compute dev name for dev %d\n", idx);
		वापस;
	पूर्ण

	dev_dir = debugfs_create_dir(devname, nfcsim_debugfs_root);
	अगर (!dev_dir) अणु
		NFCSIM_ERR(dev, "Could not create debugfs entries for nfc%d\n",
			   idx);
		वापस;
	पूर्ण

	debugfs_create_u8("dropframe", 0664, dev_dir, &dev->dropframe);
पूर्ण

अटल काष्ठा nfcsim *nfcsim_device_new(काष्ठा nfcsim_link *link_in,
					काष्ठा nfcsim_link *link_out)
अणु
	काष्ठा nfcsim *dev;
	पूर्णांक rc;

	dev = kzalloc(माप(काष्ठा nfcsim), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	INIT_DELAYED_WORK(&dev->send_work, nfcsim_send_wq);
	INIT_WORK(&dev->recv_work, nfcsim_recv_wq);

	dev->nfc_digital_dev =
			nfc_digital_allocate_device(&nfcsim_digital_ops,
						    NFC_PROTO_NFC_DEP_MASK,
						    NFCSIM_CAPABILITIES,
						    0, 0);
	अगर (!dev->nfc_digital_dev) अणु
		kमुक्त(dev);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	nfc_digital_set_drvdata(dev->nfc_digital_dev, dev);

	dev->link_in = link_in;
	dev->link_out = link_out;

	rc = nfc_digital_रेजिस्टर_device(dev->nfc_digital_dev);
	अगर (rc) अणु
		pr_err("Could not register digital device (%d)\n", rc);
		nfc_digital_मुक्त_device(dev->nfc_digital_dev);
		kमुक्त(dev);

		वापस ERR_PTR(rc);
	पूर्ण

	nfcsim_debugfs_init_dev(dev);

	वापस dev;
पूर्ण

अटल व्योम nfcsim_device_मुक्त(काष्ठा nfcsim *dev)
अणु
	nfc_digital_unरेजिस्टर_device(dev->nfc_digital_dev);

	dev->up = false;

	nfcsim_link_shutकरोwn(dev->link_in);

	cancel_delayed_work_sync(&dev->send_work);
	cancel_work_sync(&dev->recv_work);

	nfc_digital_मुक्त_device(dev->nfc_digital_dev);

	kमुक्त(dev);
पूर्ण

अटल काष्ठा nfcsim *dev0;
अटल काष्ठा nfcsim *dev1;

अटल पूर्णांक __init nfcsim_init(व्योम)
अणु
	काष्ठा nfcsim_link *link0, *link1;
	पूर्णांक rc;

	link0 = nfcsim_link_new();
	link1 = nfcsim_link_new();
	अगर (!link0 || !link1) अणु
		rc = -ENOMEM;
		जाओ निकास_err;
	पूर्ण

	nfcsim_debugfs_init();

	dev0 = nfcsim_device_new(link0, link1);
	अगर (IS_ERR(dev0)) अणु
		rc = PTR_ERR(dev0);
		जाओ निकास_err;
	पूर्ण

	dev1 = nfcsim_device_new(link1, link0);
	अगर (IS_ERR(dev1)) अणु
		nfcsim_device_मुक्त(dev0);

		rc = PTR_ERR(dev1);
		जाओ निकास_err;
	पूर्ण

	pr_info("nfcsim " NFCSIM_VERSION " initialized\n");

	वापस 0;

निकास_err:
	pr_err("Failed to initialize nfcsim driver (%d)\n", rc);

	अगर (link0)
		nfcsim_link_मुक्त(link0);
	अगर (link1)
		nfcsim_link_मुक्त(link1);

	वापस rc;
पूर्ण

अटल व्योम __निकास nfcsim_निकास(व्योम)
अणु
	काष्ठा nfcsim_link *link0, *link1;

	link0 = dev0->link_in;
	link1 = dev0->link_out;

	nfcsim_device_मुक्त(dev0);
	nfcsim_device_मुक्त(dev1);

	nfcsim_link_मुक्त(link0);
	nfcsim_link_मुक्त(link1);

	nfcsim_debugfs_हटाओ();
पूर्ण

module_init(nfcsim_init);
module_निकास(nfcsim_निकास);

MODULE_DESCRIPTION("NFCSim driver ver " NFCSIM_VERSION);
MODULE_VERSION(NFCSIM_VERSION);
MODULE_LICENSE("GPL");
