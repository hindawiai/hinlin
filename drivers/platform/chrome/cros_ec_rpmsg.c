<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2018 Google LLC.

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/slab.h>

#समावेश "cros_ec.h"

#घोषणा EC_MSG_TIMEOUT_MS	200
#घोषणा HOST_COMMAND_MARK	1
#घोषणा HOST_EVENT_MARK		2

/**
 * काष्ठा cros_ec_rpmsg_response - rpmsg message क्रमmat from from EC.
 *
 * @type:	The type of message, should be either HOST_COMMAND_MARK or
 *		HOST_EVENT_MARK, representing that the message is a response to
 *		host command, or a host event.
 * @data:	ec_host_response क्रम host command.
 */
काष्ठा cros_ec_rpmsg_response अणु
	u8 type;
	u8 data[] __aligned(4);
पूर्ण;

/**
 * काष्ठा cros_ec_rpmsg - inक्रमmation about a EC over rpmsg.
 *
 * @rpdev:	rpmsg device we are connected to
 * @xfer_ack:	completion क्रम host command transfer.
 * @host_event_work:	Work काष्ठा क्रम pending host event.
 * @ept: The rpmsg endpoपूर्णांक of this channel.
 * @has_pending_host_event: Boolean used to check अगर there is a pending event.
 * @probe_करोne: Flag to indicate that probe is करोne.
 */
काष्ठा cros_ec_rpmsg अणु
	काष्ठा rpmsg_device *rpdev;
	काष्ठा completion xfer_ack;
	काष्ठा work_काष्ठा host_event_work;
	काष्ठा rpmsg_endpoपूर्णांक *ept;
	bool has_pending_host_event;
	bool probe_करोne;
पूर्ण;

/**
 * cros_ec_cmd_xfer_rpmsg - Transfer a message over rpmsg and receive the reply
 *
 * @ec_dev: ChromeOS EC device
 * @ec_msg: Message to transfer
 *
 * This is only used क्रम old EC proto version, and is not supported क्रम this
 * driver.
 *
 * Return: -EINVAL
 */
अटल पूर्णांक cros_ec_cmd_xfer_rpmsg(काष्ठा cros_ec_device *ec_dev,
				  काष्ठा cros_ec_command *ec_msg)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * cros_ec_pkt_xfer_rpmsg - Transfer a packet over rpmsg and receive the reply
 *
 * @ec_dev: ChromeOS EC device
 * @ec_msg: Message to transfer
 *
 * Return: number of bytes of the reply on success or negative error code.
 */
अटल पूर्णांक cros_ec_pkt_xfer_rpmsg(काष्ठा cros_ec_device *ec_dev,
				  काष्ठा cros_ec_command *ec_msg)
अणु
	काष्ठा cros_ec_rpmsg *ec_rpmsg = ec_dev->priv;
	काष्ठा ec_host_response *response;
	अचिन्हित दीर्घ समयout;
	पूर्णांक len;
	पूर्णांक ret;
	u8 sum;
	पूर्णांक i;

	ec_msg->result = 0;
	len = cros_ec_prepare_tx(ec_dev, ec_msg);
	dev_dbg(ec_dev->dev, "prepared, len=%d\n", len);

	reinit_completion(&ec_rpmsg->xfer_ack);
	ret = rpmsg_send(ec_rpmsg->ept, ec_dev->करोut, len);
	अगर (ret) अणु
		dev_err(ec_dev->dev, "rpmsg send failed\n");
		वापस ret;
	पूर्ण

	समयout = msecs_to_jअगरfies(EC_MSG_TIMEOUT_MS);
	ret = रुको_क्रम_completion_समयout(&ec_rpmsg->xfer_ack, समयout);
	अगर (!ret) अणु
		dev_err(ec_dev->dev, "rpmsg send timeout\n");
		वापस -EIO;
	पूर्ण

	/* check response error code */
	response = (काष्ठा ec_host_response *)ec_dev->din;
	ec_msg->result = response->result;

	ret = cros_ec_check_result(ec_dev, ec_msg);
	अगर (ret)
		जाओ निकास;

	अगर (response->data_len > ec_msg->insize) अणु
		dev_err(ec_dev->dev, "packet too long (%d bytes, expected %d)",
			response->data_len, ec_msg->insize);
		ret = -EMSGSIZE;
		जाओ निकास;
	पूर्ण

	/* copy response packet payload and compute checksum */
	स_नकल(ec_msg->data, ec_dev->din + माप(*response),
	       response->data_len);

	sum = 0;
	क्रम (i = 0; i < माप(*response) + response->data_len; i++)
		sum += ec_dev->din[i];

	अगर (sum) अणु
		dev_err(ec_dev->dev, "bad packet checksum, calculated %x\n",
			sum);
		ret = -EBADMSG;
		जाओ निकास;
	पूर्ण

	ret = response->data_len;
निकास:
	अगर (ec_msg->command == EC_CMD_REBOOT_EC)
		msleep(EC_REBOOT_DELAY_MS);

	वापस ret;
पूर्ण

अटल व्योम
cros_ec_rpmsg_host_event_function(काष्ठा work_काष्ठा *host_event_work)
अणु
	काष्ठा cros_ec_rpmsg *ec_rpmsg = container_of(host_event_work,
						      काष्ठा cros_ec_rpmsg,
						      host_event_work);

	cros_ec_irq_thपढ़ो(0, dev_get_drvdata(&ec_rpmsg->rpdev->dev));
पूर्ण

अटल पूर्णांक cros_ec_rpmsg_callback(काष्ठा rpmsg_device *rpdev, व्योम *data,
				  पूर्णांक len, व्योम *priv, u32 src)
अणु
	काष्ठा cros_ec_device *ec_dev = dev_get_drvdata(&rpdev->dev);
	काष्ठा cros_ec_rpmsg *ec_rpmsg = ec_dev->priv;
	काष्ठा cros_ec_rpmsg_response *resp;

	अगर (!len) अणु
		dev_warn(ec_dev->dev, "rpmsg received empty response");
		वापस -EINVAL;
	पूर्ण

	resp = data;
	len -= दुरत्व(काष्ठा cros_ec_rpmsg_response, data);
	अगर (resp->type == HOST_COMMAND_MARK) अणु
		अगर (len > ec_dev->din_size) अणु
			dev_warn(ec_dev->dev,
				 "received length %d > din_size %d, truncating",
				 len, ec_dev->din_size);
			len = ec_dev->din_size;
		पूर्ण

		स_नकल(ec_dev->din, resp->data, len);
		complete(&ec_rpmsg->xfer_ack);
	पूर्ण अन्यथा अगर (resp->type == HOST_EVENT_MARK) अणु
		/*
		 * If the host event is sent beक्रमe cros_ec_रेजिस्टर is
		 * finished, queue the host event.
		 */
		अगर (ec_rpmsg->probe_करोne)
			schedule_work(&ec_rpmsg->host_event_work);
		अन्यथा
			ec_rpmsg->has_pending_host_event = true;
	पूर्ण अन्यथा अणु
		dev_warn(ec_dev->dev, "rpmsg received invalid type = %d",
			 resp->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा rpmsg_endpoपूर्णांक *
cros_ec_rpmsg_create_ept(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा rpmsg_channel_info chinfo = अणुपूर्ण;

	strscpy(chinfo.name, rpdev->id.name, RPMSG_NAME_SIZE);
	chinfo.src = rpdev->src;
	chinfo.dst = RPMSG_ADDR_ANY;

	वापस rpmsg_create_ept(rpdev, cros_ec_rpmsg_callback, शून्य, chinfo);
पूर्ण

अटल पूर्णांक cros_ec_rpmsg_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा device *dev = &rpdev->dev;
	काष्ठा cros_ec_rpmsg *ec_rpmsg;
	काष्ठा cros_ec_device *ec_dev;
	पूर्णांक ret;

	ec_dev = devm_kzalloc(dev, माप(*ec_dev), GFP_KERNEL);
	अगर (!ec_dev)
		वापस -ENOMEM;

	ec_rpmsg = devm_kzalloc(dev, माप(*ec_rpmsg), GFP_KERNEL);
	अगर (!ec_rpmsg)
		वापस -ENOMEM;

	ec_dev->dev = dev;
	ec_dev->priv = ec_rpmsg;
	ec_dev->cmd_xfer = cros_ec_cmd_xfer_rpmsg;
	ec_dev->pkt_xfer = cros_ec_pkt_xfer_rpmsg;
	ec_dev->phys_name = dev_name(&rpdev->dev);
	ec_dev->din_size = माप(काष्ठा ec_host_response) +
			   माप(काष्ठा ec_response_get_protocol_info);
	ec_dev->करोut_size = माप(काष्ठा ec_host_request);
	dev_set_drvdata(dev, ec_dev);

	ec_rpmsg->rpdev = rpdev;
	init_completion(&ec_rpmsg->xfer_ack);
	INIT_WORK(&ec_rpmsg->host_event_work,
		  cros_ec_rpmsg_host_event_function);

	ec_rpmsg->ept = cros_ec_rpmsg_create_ept(rpdev);
	अगर (!ec_rpmsg->ept)
		वापस -ENOMEM;

	ret = cros_ec_रेजिस्टर(ec_dev);
	अगर (ret < 0) अणु
		rpmsg_destroy_ept(ec_rpmsg->ept);
		cancel_work_sync(&ec_rpmsg->host_event_work);
		वापस ret;
	पूर्ण

	ec_rpmsg->probe_करोne = true;

	अगर (ec_rpmsg->has_pending_host_event)
		schedule_work(&ec_rpmsg->host_event_work);

	वापस 0;
पूर्ण

अटल व्योम cros_ec_rpmsg_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा cros_ec_device *ec_dev = dev_get_drvdata(&rpdev->dev);
	काष्ठा cros_ec_rpmsg *ec_rpmsg = ec_dev->priv;

	cros_ec_unरेजिस्टर(ec_dev);
	rpmsg_destroy_ept(ec_rpmsg->ept);
	cancel_work_sync(&ec_rpmsg->host_event_work);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cros_ec_rpmsg_suspend(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec_dev = dev_get_drvdata(dev);

	वापस cros_ec_suspend(ec_dev);
पूर्ण

अटल पूर्णांक cros_ec_rpmsg_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec_dev = dev_get_drvdata(dev);

	वापस cros_ec_resume(ec_dev);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cros_ec_rpmsg_pm_ops, cros_ec_rpmsg_suspend,
			 cros_ec_rpmsg_resume);

अटल स्थिर काष्ठा of_device_id cros_ec_rpmsg_of_match[] = अणु
	अणु .compatible = "google,cros-ec-rpmsg", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_ec_rpmsg_of_match);

अटल काष्ठा rpmsg_driver cros_ec_driver_rpmsg = अणु
	.drv = अणु
		.name   = "cros-ec-rpmsg",
		.of_match_table = cros_ec_rpmsg_of_match,
		.pm	= &cros_ec_rpmsg_pm_ops,
	पूर्ण,
	.probe		= cros_ec_rpmsg_probe,
	.हटाओ		= cros_ec_rpmsg_हटाओ,
पूर्ण;

module_rpmsg_driver(cros_ec_driver_rpmsg);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChromeOS EC multi function device (rpmsg)");
