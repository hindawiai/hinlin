<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/mhi.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>

#समावेश "qrtr.h"

काष्ठा qrtr_mhi_dev अणु
	काष्ठा qrtr_endpoपूर्णांक ep;
	काष्ठा mhi_device *mhi_dev;
	काष्ठा device *dev;
पूर्ण;

/* From MHI to QRTR */
अटल व्योम qcom_mhi_qrtr_dl_callback(काष्ठा mhi_device *mhi_dev,
				      काष्ठा mhi_result *mhi_res)
अणु
	काष्ठा qrtr_mhi_dev *qdev = dev_get_drvdata(&mhi_dev->dev);
	पूर्णांक rc;

	अगर (!qdev || mhi_res->transaction_status)
		वापस;

	rc = qrtr_endpoपूर्णांक_post(&qdev->ep, mhi_res->buf_addr,
				mhi_res->bytes_xferd);
	अगर (rc == -EINVAL)
		dev_err(qdev->dev, "invalid ipcrouter packet\n");
पूर्ण

/* From QRTR to MHI */
अटल व्योम qcom_mhi_qrtr_ul_callback(काष्ठा mhi_device *mhi_dev,
				      काष्ठा mhi_result *mhi_res)
अणु
	काष्ठा sk_buff *skb = mhi_res->buf_addr;

	अगर (skb->sk)
		sock_put(skb->sk);
	consume_skb(skb);
पूर्ण

/* Send data over MHI */
अटल पूर्णांक qcom_mhi_qrtr_send(काष्ठा qrtr_endpoपूर्णांक *ep, काष्ठा sk_buff *skb)
अणु
	काष्ठा qrtr_mhi_dev *qdev = container_of(ep, काष्ठा qrtr_mhi_dev, ep);
	पूर्णांक rc;

	अगर (skb->sk)
		sock_hold(skb->sk);

	rc = skb_linearize(skb);
	अगर (rc)
		जाओ मुक्त_skb;

	rc = mhi_queue_skb(qdev->mhi_dev, DMA_TO_DEVICE, skb, skb->len,
			   MHI_EOT);
	अगर (rc)
		जाओ मुक्त_skb;

	वापस rc;

मुक्त_skb:
	अगर (skb->sk)
		sock_put(skb->sk);
	kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल पूर्णांक qcom_mhi_qrtr_probe(काष्ठा mhi_device *mhi_dev,
			       स्थिर काष्ठा mhi_device_id *id)
अणु
	काष्ठा qrtr_mhi_dev *qdev;
	पूर्णांक rc;

	/* start channels */
	rc = mhi_prepare_क्रम_transfer(mhi_dev);
	अगर (rc)
		वापस rc;

	qdev = devm_kzalloc(&mhi_dev->dev, माप(*qdev), GFP_KERNEL);
	अगर (!qdev)
		वापस -ENOMEM;

	qdev->mhi_dev = mhi_dev;
	qdev->dev = &mhi_dev->dev;
	qdev->ep.xmit = qcom_mhi_qrtr_send;

	dev_set_drvdata(&mhi_dev->dev, qdev);
	rc = qrtr_endpoपूर्णांक_रेजिस्टर(&qdev->ep, QRTR_EP_NID_AUTO);
	अगर (rc)
		वापस rc;

	dev_dbg(qdev->dev, "Qualcomm MHI QRTR driver probed\n");

	वापस 0;
पूर्ण

अटल व्योम qcom_mhi_qrtr_हटाओ(काष्ठा mhi_device *mhi_dev)
अणु
	काष्ठा qrtr_mhi_dev *qdev = dev_get_drvdata(&mhi_dev->dev);

	qrtr_endpoपूर्णांक_unरेजिस्टर(&qdev->ep);
	mhi_unprepare_from_transfer(mhi_dev);
	dev_set_drvdata(&mhi_dev->dev, शून्य);
पूर्ण

अटल स्थिर काष्ठा mhi_device_id qcom_mhi_qrtr_id_table[] = अणु
	अणु .chan = "IPCR" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mhi, qcom_mhi_qrtr_id_table);

अटल काष्ठा mhi_driver qcom_mhi_qrtr_driver = अणु
	.probe = qcom_mhi_qrtr_probe,
	.हटाओ = qcom_mhi_qrtr_हटाओ,
	.dl_xfer_cb = qcom_mhi_qrtr_dl_callback,
	.ul_xfer_cb = qcom_mhi_qrtr_ul_callback,
	.id_table = qcom_mhi_qrtr_id_table,
	.driver = अणु
		.name = "qcom_mhi_qrtr",
	पूर्ण,
पूर्ण;

module_mhi_driver(qcom_mhi_qrtr_driver);

MODULE_AUTHOR("Chris Lew <clew@codeaurora.org>");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("Qualcomm IPC-Router MHI interface driver");
MODULE_LICENSE("GPL v2");
