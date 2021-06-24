<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications Inc.
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rpmsg.h>

#समावेश "qrtr.h"

काष्ठा qrtr_smd_dev अणु
	काष्ठा qrtr_endpoपूर्णांक ep;
	काष्ठा rpmsg_endpoपूर्णांक *channel;
	काष्ठा device *dev;
पूर्ण;

/* from smd to qrtr */
अटल पूर्णांक qcom_smd_qrtr_callback(काष्ठा rpmsg_device *rpdev,
				  व्योम *data, पूर्णांक len, व्योम *priv, u32 addr)
अणु
	काष्ठा qrtr_smd_dev *qdev = dev_get_drvdata(&rpdev->dev);
	पूर्णांक rc;

	अगर (!qdev)
		वापस -EAGAIN;

	rc = qrtr_endpoपूर्णांक_post(&qdev->ep, data, len);
	अगर (rc == -EINVAL) अणु
		dev_err(qdev->dev, "invalid ipcrouter packet\n");
		/* वापस 0 to let smd drop the packet */
		rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

/* from qrtr to smd */
अटल पूर्णांक qcom_smd_qrtr_send(काष्ठा qrtr_endpoपूर्णांक *ep, काष्ठा sk_buff *skb)
अणु
	काष्ठा qrtr_smd_dev *qdev = container_of(ep, काष्ठा qrtr_smd_dev, ep);
	पूर्णांक rc;

	rc = skb_linearize(skb);
	अगर (rc)
		जाओ out;

	rc = rpmsg_send(qdev->channel, skb->data, skb->len);

out:
	अगर (rc)
		kमुक्त_skb(skb);
	अन्यथा
		consume_skb(skb);
	वापस rc;
पूर्ण

अटल पूर्णांक qcom_smd_qrtr_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा qrtr_smd_dev *qdev;
	पूर्णांक rc;

	qdev = devm_kzalloc(&rpdev->dev, माप(*qdev), GFP_KERNEL);
	अगर (!qdev)
		वापस -ENOMEM;

	qdev->channel = rpdev->ept;
	qdev->dev = &rpdev->dev;
	qdev->ep.xmit = qcom_smd_qrtr_send;

	rc = qrtr_endpoपूर्णांक_रेजिस्टर(&qdev->ep, QRTR_EP_NID_AUTO);
	अगर (rc)
		वापस rc;

	dev_set_drvdata(&rpdev->dev, qdev);

	dev_dbg(&rpdev->dev, "Qualcomm SMD QRTR driver probed\n");

	वापस 0;
पूर्ण

अटल व्योम qcom_smd_qrtr_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा qrtr_smd_dev *qdev = dev_get_drvdata(&rpdev->dev);

	qrtr_endpoपूर्णांक_unरेजिस्टर(&qdev->ep);

	dev_set_drvdata(&rpdev->dev, शून्य);
पूर्ण

अटल स्थिर काष्ठा rpmsg_device_id qcom_smd_qrtr_smd_match[] = अणु
	अणु "IPCRTR" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा rpmsg_driver qcom_smd_qrtr_driver = अणु
	.probe = qcom_smd_qrtr_probe,
	.हटाओ = qcom_smd_qrtr_हटाओ,
	.callback = qcom_smd_qrtr_callback,
	.id_table = qcom_smd_qrtr_smd_match,
	.drv = अणु
		.name = "qcom_smd_qrtr",
	पूर्ण,
पूर्ण;

module_rpmsg_driver(qcom_smd_qrtr_driver);

MODULE_ALIAS("rpmsg:IPCRTR");
MODULE_DESCRIPTION("Qualcomm IPC-Router SMD interface driver");
MODULE_LICENSE("GPL v2");
