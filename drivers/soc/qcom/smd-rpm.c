<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications AB.
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश <linux/rpmsg.h>
#समावेश <linux/soc/qcom/smd-rpm.h>

#घोषणा RPM_REQUEST_TIMEOUT     (5 * HZ)

/**
 * काष्ठा qcom_smd_rpm - state of the rpm device driver
 * @rpm_channel:	reference to the smd channel
 * @icc:		पूर्णांकerconnect proxy device
 * @dev:		rpm device
 * @ack:		completion क्रम acks
 * @lock:		mutual exclusion around the send/complete pair
 * @ack_status:		result of the rpm request
 */
काष्ठा qcom_smd_rpm अणु
	काष्ठा rpmsg_endpoपूर्णांक *rpm_channel;
	काष्ठा platक्रमm_device *icc;
	काष्ठा device *dev;

	काष्ठा completion ack;
	काष्ठा mutex lock;
	पूर्णांक ack_status;
पूर्ण;

/**
 * काष्ठा qcom_rpm_header - header क्रम all rpm requests and responses
 * @service_type:	identअगरier of the service
 * @length:		length of the payload
 */
काष्ठा qcom_rpm_header अणु
	__le32 service_type;
	__le32 length;
पूर्ण;

/**
 * काष्ठा qcom_rpm_request - request message to the rpm
 * @msg_id:	identअगरier of the outgoing message
 * @flags:	active/sleep state flags
 * @type:	resource type
 * @id:		resource id
 * @data_len:	length of the payload following this header
 */
काष्ठा qcom_rpm_request अणु
	__le32 msg_id;
	__le32 flags;
	__le32 type;
	__le32 id;
	__le32 data_len;
पूर्ण;

/**
 * काष्ठा qcom_rpm_message - response message from the rpm
 * @msg_type:	indicator of the type of message
 * @length:	the size of this message, including the message header
 * @msg_id:	message id
 * @message:	textual message from the rpm
 *
 * Multiple of these messages can be stacked in an rpm message.
 */
काष्ठा qcom_rpm_message अणु
	__le32 msg_type;
	__le32 length;
	जोड़ अणु
		__le32 msg_id;
		u8 message[0];
	पूर्ण;
पूर्ण;

#घोषणा RPM_SERVICE_TYPE_REQUEST	0x00716572 /* "req\0" */

#घोषणा RPM_MSG_TYPE_ERR		0x00727265 /* "err\0" */
#घोषणा RPM_MSG_TYPE_MSG_ID		0x2367736d /* "msg#" */

/**
 * qcom_rpm_smd_ग_लिखो - ग_लिखो @buf to @type:@id
 * @rpm:	rpm handle
 * @state:	active/sleep state flags
 * @type:	resource type
 * @id:		resource identअगरier
 * @buf:	the data to be written
 * @count:	number of bytes in @buf
 */
पूर्णांक qcom_rpm_smd_ग_लिखो(काष्ठा qcom_smd_rpm *rpm,
		       पूर्णांक state,
		       u32 type, u32 id,
		       व्योम *buf,
		       माप_प्रकार count)
अणु
	अटल अचिन्हित msg_id = 1;
	पूर्णांक left;
	पूर्णांक ret;
	काष्ठा अणु
		काष्ठा qcom_rpm_header hdr;
		काष्ठा qcom_rpm_request req;
		u8 payload[];
	पूर्ण *pkt;
	माप_प्रकार size = माप(*pkt) + count;

	/* SMD packets to the RPM may not exceed 256 bytes */
	अगर (WARN_ON(size >= 256))
		वापस -EINVAL;

	pkt = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	mutex_lock(&rpm->lock);

	pkt->hdr.service_type = cpu_to_le32(RPM_SERVICE_TYPE_REQUEST);
	pkt->hdr.length = cpu_to_le32(माप(काष्ठा qcom_rpm_request) + count);

	pkt->req.msg_id = cpu_to_le32(msg_id++);
	pkt->req.flags = cpu_to_le32(state);
	pkt->req.type = cpu_to_le32(type);
	pkt->req.id = cpu_to_le32(id);
	pkt->req.data_len = cpu_to_le32(count);
	स_नकल(pkt->payload, buf, count);

	ret = rpmsg_send(rpm->rpm_channel, pkt, size);
	अगर (ret)
		जाओ out;

	left = रुको_क्रम_completion_समयout(&rpm->ack, RPM_REQUEST_TIMEOUT);
	अगर (!left)
		ret = -ETIMEDOUT;
	अन्यथा
		ret = rpm->ack_status;

out:
	kमुक्त(pkt);
	mutex_unlock(&rpm->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_rpm_smd_ग_लिखो);

अटल पूर्णांक qcom_smd_rpm_callback(काष्ठा rpmsg_device *rpdev,
				 व्योम *data,
				 पूर्णांक count,
				 व्योम *priv,
				 u32 addr)
अणु
	स्थिर काष्ठा qcom_rpm_header *hdr = data;
	माप_प्रकार hdr_length = le32_to_cpu(hdr->length);
	स्थिर काष्ठा qcom_rpm_message *msg;
	काष्ठा qcom_smd_rpm *rpm = dev_get_drvdata(&rpdev->dev);
	स्थिर u8 *buf = data + माप(काष्ठा qcom_rpm_header);
	स्थिर u8 *end = buf + hdr_length;
	अक्षर msgbuf[32];
	पूर्णांक status = 0;
	u32 len, msg_length;

	अगर (le32_to_cpu(hdr->service_type) != RPM_SERVICE_TYPE_REQUEST ||
	    hdr_length < माप(काष्ठा qcom_rpm_message)) अणु
		dev_err(rpm->dev, "invalid request\n");
		वापस 0;
	पूर्ण

	जबतक (buf < end) अणु
		msg = (काष्ठा qcom_rpm_message *)buf;
		msg_length = le32_to_cpu(msg->length);
		चयन (le32_to_cpu(msg->msg_type)) अणु
		हाल RPM_MSG_TYPE_MSG_ID:
			अवरोध;
		हाल RPM_MSG_TYPE_ERR:
			len = min_t(u32, ALIGN(msg_length, 4), माप(msgbuf));
			स_नकल_fromio(msgbuf, msg->message, len);
			msgbuf[len - 1] = 0;

			अगर (!म_भेद(msgbuf, "resource does not exist"))
				status = -ENXIO;
			अन्यथा
				status = -EINVAL;
			अवरोध;
		पूर्ण

		buf = PTR_ALIGN(buf + 2 * माप(u32) + msg_length, 4);
	पूर्ण

	rpm->ack_status = status;
	complete(&rpm->ack);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_smd_rpm_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा qcom_smd_rpm *rpm;
	पूर्णांक ret;

	rpm = devm_kzalloc(&rpdev->dev, माप(*rpm), GFP_KERNEL);
	अगर (!rpm)
		वापस -ENOMEM;

	mutex_init(&rpm->lock);
	init_completion(&rpm->ack);

	rpm->dev = &rpdev->dev;
	rpm->rpm_channel = rpdev->ept;
	dev_set_drvdata(&rpdev->dev, rpm);

	rpm->icc = platक्रमm_device_रेजिस्टर_data(&rpdev->dev, "icc_smd_rpm", -1,
						 शून्य, 0);
	अगर (IS_ERR(rpm->icc))
		वापस PTR_ERR(rpm->icc);

	ret = of_platक्रमm_populate(rpdev->dev.of_node, शून्य, शून्य, &rpdev->dev);
	अगर (ret)
		platक्रमm_device_unरेजिस्टर(rpm->icc);

	वापस ret;
पूर्ण

अटल व्योम qcom_smd_rpm_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा qcom_smd_rpm *rpm = dev_get_drvdata(&rpdev->dev);

	platक्रमm_device_unरेजिस्टर(rpm->icc);
	of_platक्रमm_depopulate(&rpdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_smd_rpm_of_match[] = अणु
	अणु .compatible = "qcom,rpm-apq8084" पूर्ण,
	अणु .compatible = "qcom,rpm-ipq6018" पूर्ण,
	अणु .compatible = "qcom,rpm-msm8916" पूर्ण,
	अणु .compatible = "qcom,rpm-msm8936" पूर्ण,
	अणु .compatible = "qcom,rpm-msm8974" पूर्ण,
	अणु .compatible = "qcom,rpm-msm8976" पूर्ण,
	अणु .compatible = "qcom,rpm-msm8994" पूर्ण,
	अणु .compatible = "qcom,rpm-msm8996" पूर्ण,
	अणु .compatible = "qcom,rpm-msm8998" पूर्ण,
	अणु .compatible = "qcom,rpm-sdm660" पूर्ण,
	अणु .compatible = "qcom,rpm-qcs404" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_smd_rpm_of_match);

अटल काष्ठा rpmsg_driver qcom_smd_rpm_driver = अणु
	.probe = qcom_smd_rpm_probe,
	.हटाओ = qcom_smd_rpm_हटाओ,
	.callback = qcom_smd_rpm_callback,
	.drv  = अणु
		.name  = "qcom_smd_rpm",
		.of_match_table = qcom_smd_rpm_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_smd_rpm_init(व्योम)
अणु
	वापस रेजिस्टर_rpmsg_driver(&qcom_smd_rpm_driver);
पूर्ण
arch_initcall(qcom_smd_rpm_init);

अटल व्योम __निकास qcom_smd_rpm_निकास(व्योम)
अणु
	unरेजिस्टर_rpmsg_driver(&qcom_smd_rpm_driver);
पूर्ण
module_निकास(qcom_smd_rpm_निकास);

MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@sonymobile.com>");
MODULE_DESCRIPTION("Qualcomm SMD backed RPM driver");
MODULE_LICENSE("GPL v2");
