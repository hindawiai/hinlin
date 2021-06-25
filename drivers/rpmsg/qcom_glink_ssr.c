<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2017, The Linux Foundation. All rights reserved.
 * Copyright (c) 2017, Linaro Ltd.
 */

#समावेश <linux/completion.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/rpmsg/qcom_glink.h>
#समावेश <linux/remoteproc/qcom_rproc.h>

/**
 * काष्ठा करो_cleanup_msg - The data काष्ठाure क्रम an SSR करो_cleanup message
 * @version:	The G-Link SSR protocol version
 * @command:	The G-Link SSR command - करो_cleanup
 * @seq_num:	Sequence number
 * @name_len:	Length of the name of the subप्रणाली being restarted
 * @name:	G-Link edge name of the subप्रणाली being restarted
 */
काष्ठा करो_cleanup_msg अणु
	__le32 version;
	__le32 command;
	__le32 seq_num;
	__le32 name_len;
	अक्षर name[32];
पूर्ण;

/**
 * काष्ठा cleanup_करोne_msg - The data काष्ठाure क्रम an SSR cleanup_करोne message
 * @version:	The G-Link SSR protocol version
 * @response:	The G-Link SSR response to a करो_cleanup command, cleanup_करोne
 * @seq_num:	Sequence number
 */
काष्ठा cleanup_करोne_msg अणु
	__le32 version;
	__le32 response;
	__le32 seq_num;
पूर्ण;

/**
 * G-Link SSR protocol commands
 */
#घोषणा GLINK_SSR_DO_CLEANUP	0
#घोषणा GLINK_SSR_CLEANUP_DONE	1

काष्ठा glink_ssr अणु
	काष्ठा device *dev;
	काष्ठा rpmsg_endpoपूर्णांक *ept;

	काष्ठा notअगरier_block nb;

	u32 seq_num;
	काष्ठा completion completion;
पूर्ण;

/* Notअगरier list क्रम all रेजिस्टरed glink_ssr instances */
अटल BLOCKING_NOTIFIER_HEAD(ssr_notअगरiers);

/**
 * qcom_glink_ssr_notअगरy() - notअगरy GLINK SSR about stopped remoteproc
 * @ssr_name:	name of the remoteproc that has been stopped
 */
व्योम qcom_glink_ssr_notअगरy(स्थिर अक्षर *ssr_name)
अणु
	blocking_notअगरier_call_chain(&ssr_notअगरiers, 0, (व्योम *)ssr_name);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_glink_ssr_notअगरy);

अटल पूर्णांक qcom_glink_ssr_callback(काष्ठा rpmsg_device *rpdev,
				   व्योम *data, पूर्णांक len, व्योम *priv, u32 addr)
अणु
	काष्ठा cleanup_करोne_msg *msg = data;
	काष्ठा glink_ssr *ssr = dev_get_drvdata(&rpdev->dev);

	अगर (len < माप(*msg)) अणु
		dev_err(ssr->dev, "message too short\n");
		वापस -EINVAL;
	पूर्ण

	अगर (le32_to_cpu(msg->version) != 0)
		वापस -EINVAL;

	अगर (le32_to_cpu(msg->response) != GLINK_SSR_CLEANUP_DONE)
		वापस 0;

	अगर (le32_to_cpu(msg->seq_num) != ssr->seq_num) अणु
		dev_err(ssr->dev, "invalid sequence number of response\n");
		वापस -EINVAL;
	पूर्ण

	complete(&ssr->completion);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_glink_ssr_notअगरier_call(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ event,
					व्योम *data)
अणु
	काष्ठा glink_ssr *ssr = container_of(nb, काष्ठा glink_ssr, nb);
	काष्ठा करो_cleanup_msg msg;
	अक्षर *ssr_name = data;
	पूर्णांक ret;

	ssr->seq_num++;
	reinit_completion(&ssr->completion);

	स_रखो(&msg, 0, माप(msg));
	msg.command = cpu_to_le32(GLINK_SSR_DO_CLEANUP);
	msg.seq_num = cpu_to_le32(ssr->seq_num);
	msg.name_len = cpu_to_le32(म_माप(ssr_name));
	strlcpy(msg.name, ssr_name, माप(msg.name));

	ret = rpmsg_send(ssr->ept, &msg, माप(msg));
	अगर (ret < 0)
		dev_err(ssr->dev, "failed to send cleanup message\n");

	ret = रुको_क्रम_completion_समयout(&ssr->completion, HZ);
	अगर (!ret)
		dev_err(ssr->dev, "timeout waiting for cleanup done message\n");

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक qcom_glink_ssr_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा glink_ssr *ssr;

	ssr = devm_kzalloc(&rpdev->dev, माप(*ssr), GFP_KERNEL);
	अगर (!ssr)
		वापस -ENOMEM;

	init_completion(&ssr->completion);

	ssr->dev = &rpdev->dev;
	ssr->ept = rpdev->ept;
	ssr->nb.notअगरier_call = qcom_glink_ssr_notअगरier_call;

	dev_set_drvdata(&rpdev->dev, ssr);

	वापस blocking_notअगरier_chain_रेजिस्टर(&ssr_notअगरiers, &ssr->nb);
पूर्ण

अटल व्योम qcom_glink_ssr_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा glink_ssr *ssr = dev_get_drvdata(&rpdev->dev);

	blocking_notअगरier_chain_unरेजिस्टर(&ssr_notअगरiers, &ssr->nb);
पूर्ण

अटल स्थिर काष्ठा rpmsg_device_id qcom_glink_ssr_match[] = अणु
	अणु "glink_ssr" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा rpmsg_driver qcom_glink_ssr_driver = अणु
	.probe = qcom_glink_ssr_probe,
	.हटाओ = qcom_glink_ssr_हटाओ,
	.callback = qcom_glink_ssr_callback,
	.id_table = qcom_glink_ssr_match,
	.drv = अणु
		.name = "qcom_glink_ssr",
	पूर्ण,
पूर्ण;
module_rpmsg_driver(qcom_glink_ssr_driver);
