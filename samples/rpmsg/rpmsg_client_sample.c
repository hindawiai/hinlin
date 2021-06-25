<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Remote processor messaging - sample client driver
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rpmsg.h>

#घोषणा MSG		"hello world!"

अटल पूर्णांक count = 100;
module_param(count, पूर्णांक, 0644);

काष्ठा instance_data अणु
	पूर्णांक rx_count;
पूर्ण;

अटल पूर्णांक rpmsg_sample_cb(काष्ठा rpmsg_device *rpdev, व्योम *data, पूर्णांक len,
						व्योम *priv, u32 src)
अणु
	पूर्णांक ret;
	काष्ठा instance_data *idata = dev_get_drvdata(&rpdev->dev);

	dev_info(&rpdev->dev, "incoming msg %d (src: 0x%x)\n",
		 ++idata->rx_count, src);

	prपूर्णांक_hex_dump_debug(__func__, DUMP_PREFIX_NONE, 16, 1, data, len,
			     true);

	/* samples should not live क्रमever */
	अगर (idata->rx_count >= count) अणु
		dev_info(&rpdev->dev, "goodbye!\n");
		वापस 0;
	पूर्ण

	/* send a new message now */
	ret = rpmsg_send(rpdev->ept, MSG, म_माप(MSG));
	अगर (ret)
		dev_err(&rpdev->dev, "rpmsg_send failed: %d\n", ret);

	वापस 0;
पूर्ण

अटल पूर्णांक rpmsg_sample_probe(काष्ठा rpmsg_device *rpdev)
अणु
	पूर्णांक ret;
	काष्ठा instance_data *idata;

	dev_info(&rpdev->dev, "new channel: 0x%x -> 0x%x!\n",
					rpdev->src, rpdev->dst);

	idata = devm_kzalloc(&rpdev->dev, माप(*idata), GFP_KERNEL);
	अगर (!idata)
		वापस -ENOMEM;

	dev_set_drvdata(&rpdev->dev, idata);

	/* send a message to our remote processor */
	ret = rpmsg_send(rpdev->ept, MSG, म_माप(MSG));
	अगर (ret) अणु
		dev_err(&rpdev->dev, "rpmsg_send failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rpmsg_sample_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	dev_info(&rpdev->dev, "rpmsg sample client driver is removed\n");
पूर्ण

अटल काष्ठा rpmsg_device_id rpmsg_driver_sample_id_table[] = अणु
	अणु .name	= "rpmsg-client-sample" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(rpmsg, rpmsg_driver_sample_id_table);

अटल काष्ठा rpmsg_driver rpmsg_sample_client = अणु
	.drv.name	= KBUILD_MODNAME,
	.id_table	= rpmsg_driver_sample_id_table,
	.probe		= rpmsg_sample_probe,
	.callback	= rpmsg_sample_cb,
	.हटाओ		= rpmsg_sample_हटाओ,
पूर्ण;
module_rpmsg_driver(rpmsg_sample_client);

MODULE_DESCRIPTION("Remote processor messaging sample client driver");
MODULE_LICENSE("GPL v2");
