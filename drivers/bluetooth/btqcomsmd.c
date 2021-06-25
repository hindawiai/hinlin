<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, Linaro Ltd.
 * Copyright (c) 2015, Sony Mobile Communications Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/of.h>

#समावेश <linux/soc/qcom/wcnss_ctrl.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btqca.h"

काष्ठा btqcomsmd अणु
	काष्ठा hci_dev *hdev;

	काष्ठा rpmsg_endpoपूर्णांक *acl_channel;
	काष्ठा rpmsg_endpoपूर्णांक *cmd_channel;
पूर्ण;

अटल पूर्णांक btqcomsmd_recv(काष्ठा hci_dev *hdev, अचिन्हित पूर्णांक type,
			   स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा sk_buff *skb;

	/* Use GFP_ATOMIC as we're in IRQ context */
	skb = bt_skb_alloc(count, GFP_ATOMIC);
	अगर (!skb) अणु
		hdev->stat.err_rx++;
		वापस -ENOMEM;
	पूर्ण

	hci_skb_pkt_type(skb) = type;
	skb_put_data(skb, data, count);

	वापस hci_recv_frame(hdev, skb);
पूर्ण

अटल पूर्णांक btqcomsmd_acl_callback(काष्ठा rpmsg_device *rpdev, व्योम *data,
				  पूर्णांक count, व्योम *priv, u32 addr)
अणु
	काष्ठा btqcomsmd *btq = priv;

	btq->hdev->stat.byte_rx += count;
	वापस btqcomsmd_recv(btq->hdev, HCI_ACLDATA_PKT, data, count);
पूर्ण

अटल पूर्णांक btqcomsmd_cmd_callback(काष्ठा rpmsg_device *rpdev, व्योम *data,
				  पूर्णांक count, व्योम *priv, u32 addr)
अणु
	काष्ठा btqcomsmd *btq = priv;

	btq->hdev->stat.byte_rx += count;
	वापस btqcomsmd_recv(btq->hdev, HCI_EVENT_PKT, data, count);
पूर्ण

अटल पूर्णांक btqcomsmd_send(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा btqcomsmd *btq = hci_get_drvdata(hdev);
	पूर्णांक ret;

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_ACLDATA_PKT:
		ret = rpmsg_send(btq->acl_channel, skb->data, skb->len);
		अगर (ret) अणु
			hdev->stat.err_tx++;
			अवरोध;
		पूर्ण
		hdev->stat.acl_tx++;
		hdev->stat.byte_tx += skb->len;
		अवरोध;
	हाल HCI_COMMAND_PKT:
		ret = rpmsg_send(btq->cmd_channel, skb->data, skb->len);
		अगर (ret) अणु
			hdev->stat.err_tx++;
			अवरोध;
		पूर्ण
		hdev->stat.cmd_tx++;
		hdev->stat.byte_tx += skb->len;
		अवरोध;
	शेष:
		ret = -EILSEQ;
		अवरोध;
	पूर्ण

	अगर (!ret)
		kमुक्त_skb(skb);

	वापस ret;
पूर्ण

अटल पूर्णांक btqcomsmd_खोलो(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक btqcomsmd_बंद(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक btqcomsmd_setup(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);
	kमुक्त_skb(skb);

	/* Devices करो not have persistent storage क्रम BD address. Retrieve
	 * it from the firmware node property.
	 */
	set_bit(HCI_QUIRK_USE_BDADDR_PROPERTY, &hdev->quirks);

	वापस 0;
पूर्ण

अटल पूर्णांक btqcomsmd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा btqcomsmd *btq;
	काष्ठा hci_dev *hdev;
	व्योम *wcnss;
	पूर्णांक ret;

	btq = devm_kzalloc(&pdev->dev, माप(*btq), GFP_KERNEL);
	अगर (!btq)
		वापस -ENOMEM;

	wcnss = dev_get_drvdata(pdev->dev.parent);

	btq->acl_channel = qcom_wcnss_खोलो_channel(wcnss, "APPS_RIVA_BT_ACL",
						   btqcomsmd_acl_callback, btq);
	अगर (IS_ERR(btq->acl_channel))
		वापस PTR_ERR(btq->acl_channel);

	btq->cmd_channel = qcom_wcnss_खोलो_channel(wcnss, "APPS_RIVA_BT_CMD",
						   btqcomsmd_cmd_callback, btq);
	अगर (IS_ERR(btq->cmd_channel)) अणु
		ret = PTR_ERR(btq->cmd_channel);
		जाओ destroy_acl_channel;
	पूर्ण

	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		ret = -ENOMEM;
		जाओ destroy_cmd_channel;
	पूर्ण

	hci_set_drvdata(hdev, btq);
	btq->hdev = hdev;
	SET_HCIDEV_DEV(hdev, &pdev->dev);

	hdev->bus = HCI_SMD;
	hdev->खोलो = btqcomsmd_खोलो;
	hdev->बंद = btqcomsmd_बंद;
	hdev->send = btqcomsmd_send;
	hdev->setup = btqcomsmd_setup;
	hdev->set_bdaddr = qca_set_bdaddr_rome;

	ret = hci_रेजिस्टर_dev(hdev);
	अगर (ret < 0)
		जाओ hci_मुक्त_dev;

	platक्रमm_set_drvdata(pdev, btq);

	वापस 0;

hci_मुक्त_dev:
	hci_मुक्त_dev(hdev);
destroy_cmd_channel:
	rpmsg_destroy_ept(btq->cmd_channel);
destroy_acl_channel:
	rpmsg_destroy_ept(btq->acl_channel);

	वापस ret;
पूर्ण

अटल पूर्णांक btqcomsmd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा btqcomsmd *btq = platक्रमm_get_drvdata(pdev);

	hci_unरेजिस्टर_dev(btq->hdev);
	hci_मुक्त_dev(btq->hdev);

	rpmsg_destroy_ept(btq->cmd_channel);
	rpmsg_destroy_ept(btq->acl_channel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id btqcomsmd_of_match[] = अणु
	अणु .compatible = "qcom,wcnss-bt", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, btqcomsmd_of_match);

अटल काष्ठा platक्रमm_driver btqcomsmd_driver = अणु
	.probe = btqcomsmd_probe,
	.हटाओ = btqcomsmd_हटाओ,
	.driver  = अणु
		.name  = "btqcomsmd",
		.of_match_table = btqcomsmd_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(btqcomsmd_driver);

MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@sonymobile.com>");
MODULE_DESCRIPTION("Qualcomm SMD HCI driver");
MODULE_LICENSE("GPL v2");
